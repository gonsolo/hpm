project(HPM)

add_executable(hpm2tiff hpm2tiff.cc)
target_link_libraries(hpm2tiff tiff)
add_executable(tiff2hpm tiff2hpm.cc)
target_link_libraries(tiff2hpm tiff)

