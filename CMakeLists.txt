cmake_minimum_required(VERSION 3.7)

project(HPM)

if(APPLE)
include_directories(/usr/local/Cellar/libtiff/4.0.7_2/include)
link_directories(/usr/local/Cellar/libtiff/4.0.7_2/lib)
endif()

add_executable(hpm2tiff hpm2tiff.cc)
target_link_libraries(hpm2tiff tiff)
add_executable(tiff2hpm tiff2hpm.cc)
target_link_libraries(tiff2hpm tiff)

