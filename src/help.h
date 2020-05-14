#include <iostream>
#include "string.h"

using namespace std;

bool write_file(string filename, const char* buf, unsigned long buf_len);

bool write_tileset(
	double longti, double lati,
	double tile_w, double tile_h,
	double height_min, double height_max,
	double geometricError,
	const char* filename, string full_path, string& str, double* region
);


	double degree2rad(double val);
	double lati_to_meter(double diff);
	double longti_to_meter(double diff, double lati);
	double meter_to_lati(double m);
	double meter_to_longti(double m, double lati);



