#include <iostream>
#include <boost/program_options.hpp>
#include "shapTo3Dtiles.h"
#pragma once
//#include "spdlog/cfg/env.h"

using namespace std;
namespace  po = boost::program_options;


//void load_levels_example()
//{
//    spdlog::cfg::load_env_levels();
//}
int main(int ac, char* av[])
{
    // Log levels can be loaded from argv/env using "SPDLOG_LEVEL"
   // load_levels_example();
    //spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

    try {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("sourceDirectory", po::value<std::string>())
            ("targetDirectory", po::value<std::string>(), "set path")
            ("buildingHeight", po::value<std::string>(), "height")
            ;

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);

        if (vm.count("sourceDirectory")) {
            cout << "sourceDirectory was set to "
                << vm["sourceDirectory"].as<string>() << ".\n";
        }
        else {
            cout << "sourceDirectory was not set.\n";
        }
    
        if (vm.count("targetDirectory")) {
            cout << "targetDirectory are : "
                << vm["targetDirectory"].as<string>() << ".\n";
        }
        else {
            cout << "targetDirectory was not set.\n";
        }

        if (vm.count("buildingHeight")) {
            cout << "buildingHeight are :  "
                << vm["buildingHeight"].as<string>() << ".\n";
        }
        else {
            cout << "buildingHeight  was not set.\n";
        }
        const char* filename = vm["sourceDirectory"].as<string>().c_str();
        const char* dest = vm["targetDirectory"].as<string>().c_str();
        const char* height = vm["buildingHeight"].as<std::string>().c_str();

        ShapTo3Dtiles(filename, dest, height);
    }
    catch (exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch (...) {
        cerr << "Exception of unknown type!\n";
    }
    	
	//const char* filename = "F:\\ShapeData\\building.shp";
	//int layer_id = 0;
	//const char* dest = "D:\\temp";
	//const char* height = "10";
	//printf("%s\n", argv[1]);
	//printf("%d\n", atoi(argv[2]));
	//printf("%s\n", argv[3]);
	//printf("%s\n", argv[4]);
	//ShapTo3Dtiles(filename, layer_id, dest, height);
}