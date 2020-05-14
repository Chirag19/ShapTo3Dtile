cmake_minimum_required(VERSION 3.5.1)
project(ShapeTo3Dtile)

   # set path to additional CMake modules
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 11)

# include directories
include_directories(
		third_party/osg
        third_party/
)

# link_directories(
# ${catkin_LIB_DIRS} ../third_party/lib ../third_party/lib2)
link_libraries(
        ../third_party/lib/osgd
		../third_party/lib2/gdal_i
		../third_party/lib2/libboost_filesystem-vc142-mt-sgd-x64-1_70
		../third_party/lib2/libboost_program_options-vc142-mt-sgd-x64-1_70
)

add_executable(ShapeTo3Dtile src/main.cpp src/shapTo3Dtiles.h src/help.h src/linkClasss.h src/tiny_gltf.h src/earcut.hpp src/help.cpp src/json.hpp src/linkClasss.cpp 
 src/shapTo3Dtiles.cpp src/tileset.cpp)
