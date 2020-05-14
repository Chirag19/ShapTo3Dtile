#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

#include "gdal/ogr_spatialref.h"
#include "gdal/ogrsf_frmts.h"
#include "help.h"

static const double pi = std::acos(-1);

double degree2rad(double val) {
    return val * pi / 180.0;
}
double lati_to_meter(double diff) {
    return diff / 0.000000157891;
}

double longti_to_meter(double diff, double lati) {
    return diff / 0.000000156785 * std::cos(lati);
}

double meter_to_lati(double m) {
    return m * 0.000000157891;
}

double meter_to_longti(double m, double lati) {
    return m * 0.000000156785 / std::cos(lati);
}

static bool flag = true;
/**
根据经纬度，生成tileset
*/
bool write_tileset(
    double radian_x, double radian_y,
    double tile_w, double tile_h,
    double height_min, double height_max,
    double geometricError,
    const char* filename, string full_path, string &tileset, double* regions
) {

    double ellipsod_a = 40680631590769;
    double ellipsod_b = 40680631590769;
    double ellipsod_c = 40408299984661.4;

    const double pi = std::acos(-1);
    double xn = std::cos(radian_x) * std::cos(radian_y);
    double yn = std::sin(radian_x) * std::cos(radian_y);
    double zn = std::sin(radian_y);

    double x0 = ellipsod_a * xn;
    double y0 = ellipsod_b * yn;
    double z0 = ellipsod_c * zn;
    double gamma = std::sqrt(xn * x0 + yn * y0 + zn * z0);
    double px = x0 / gamma;
    double py = y0 / gamma;
    double pz = z0 / gamma;
    double dx = x0 * height_min;
    double dy = y0 * height_min;
    double dz = z0 * height_min;

    std::vector<double> east_mat = { -y0,x0,0 };
    std::vector<double> north_mat = {
        (y0 * east_mat[2] - east_mat[1] * z0),
        (z0 * east_mat[0] - east_mat[2] * x0),
        (x0 * east_mat[1] - east_mat[0] * y0)
    };
    double east_normal = std::sqrt(
        east_mat[0] * east_mat[0] +
        east_mat[1] * east_mat[1] +
        east_mat[2] * east_mat[2]
    );
    double north_normal = std::sqrt(
        north_mat[0] * north_mat[0] +
        north_mat[1] * north_mat[1] +
        north_mat[2] * north_mat[2]
    );

    std::vector<double> matrix = {
        east_mat[0] / east_normal,
        east_mat[1] / east_normal,
        east_mat[2] / east_normal,
        0,
        north_mat[0] / north_normal,
        north_mat[1] / north_normal,
        north_mat[2] / north_normal,
        0,
        xn,
        yn,
        zn,
        0,
        px + dx,
        py + dy,
        pz + dz,
        1
    };

    std::vector<double> region = {
        radian_x - meter_to_longti(tile_w / 2, radian_y),
        radian_y - meter_to_lati(tile_h / 2),
        radian_x + meter_to_longti(tile_w / 2, radian_y),
        radian_y + meter_to_lati(tile_h / 2),
        0,
        height_max
    };
    if (flag)
    {
        regions[0] = region[0];
        regions[1] = region[1];
        regions[2] = region[2];
        regions[3] = region[3];
        regions[4] = region[4];
        regions[5] = region[5];
        flag = false;
    }
    else
    {
        regions[0] = regions[0] > region[0] ? region[0] : regions[0];
        regions[1] = regions[1] > region[1] ? region[1] : regions[1];
        regions[2] = regions[2] < region[2] ? region[2] : regions[2];
        regions[3] = regions[3] < region[3] ? region[3] : regions[3];
        regions[4] = regions[4] > region[4] ? region[4] : regions[4];
        regions[5] = regions[5] < region[5] ? region[5] : regions[5];
    }   
    tileset += std::to_string(region[0]);
    tileset += ",\n";
    tileset += std::to_string(region[1]);
    tileset += ",\n";
    tileset += std::to_string(region[2]);
    tileset += ",\n";
    tileset += std::to_string(region[3]);
    tileset += ",\n";
    tileset += std::to_string(region[4]);
    tileset += ",\n";
    tileset += std::to_string(region[5]);
    tileset += "\n]\n},\n \"content\": {\"uri\":\"";
    tileset += filename;
    tileset += "\"\n},\n\"geometricError\":";
    tileset += std::to_string(geometricError);
    tileset += ",\n\"refine\": \"REPLACE\",\n\"transform\": [";
    for (int i = 0; i < 15; i++) {
        tileset += std::to_string(matrix[i]);
        tileset += ",";
    }
    tileset += "1\n]\n}\n";

    std::string json_txt = "{\n\"asset\": {\
                \"version\": \"0.0\",\
                \"gltfUpAxis\": \"Y\"\
            },\
            \"geometricError\":";
    json_txt += std::to_string(geometricError);
    json_txt += ",\"root\": {\
                \"transform\": [";
    for (int i = 0; i < 15; i++) {
        json_txt += std::to_string(matrix[i]);
        json_txt += ",";
    }
    json_txt += "1],\
                \"boundingVolume\": {\
                    \"region\": [";
    for (int i = 0; i < 5; i++) {
        json_txt += std::to_string(region[i]);
        json_txt += ",";
    }
    json_txt += std::to_string(region[5]);

    char last_buf[512];
   /* sprintf(last_buf, "]},\"geometricError\": %f,\
                        \"refine\": \"REPLACE\",\
                        \"content\": {\
                            \"uri\": \"%s\"}}}", geometricError, filename);*/
    sprintf_s(last_buf, "]},\"geometricError\": %f,\
                        \"refine\": \"REPLACE\",\
                        \"content\": {\
                            \"uri\": \"%s\"}}}", geometricError, filename);

    json_txt += last_buf;

    bool ret = write_file(full_path, json_txt.data(), json_txt.size());
    if (!ret) {
        //LOG_E("write file %s fail", filename);
    }
    return ret;
}