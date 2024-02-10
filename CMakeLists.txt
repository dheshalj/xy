cmake_minimum_required(VERSION 3.10)

project(xy)

add_executable(xy xy.cpp)

add_library(ini STATIC ini/ini.c ini/ini.h)
add_library(INIReader STATIC ini/INIReader.cpp ini/INIReader.h)
target_link_libraries(ini PUBLIC xy)
target_link_libraries(INIReader PUBLIC xy)