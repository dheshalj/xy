cmake_minimum_required(VERSION 3.10)

project(xy)


add_library(ini OBJECT ini/ini.c ini/ini.h)
target_include_directories(ini PUBLIC include)
target_compile_features(ini PUBLIC cxx_std_11)

add_library(INIReader OBJECT ini/INIReader.cpp ini/INIReader.h)
target_include_directories(INIReader PUBLIC include)
target_compile_features(INIReader PUBLIC cxx_std_11)

add_executable(xy xy.cpp)

target_link_libraries(xy PUBLIC ini)
target_link_libraries(xy PUBLIC INIReader)