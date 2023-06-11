cmake_minimum_required(VERSION 3.2)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_BUILD_RPATH app)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BUILD_RPATH}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_RPATH}/bin)

project(wort LANGUAGES CXX)

add_library(wo_count STATIC wort.h wort.cpp output.h output.cpp)

add_executable(wort main.cpp)
target_link_libraries(wort wo_count)