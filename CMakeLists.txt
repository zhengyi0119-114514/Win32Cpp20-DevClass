cmake_minimum_required(VERSION 3.20)
project(Win32Cpp20DevClassLib CXX C)

add_library(Win32ClassLib)
target_include_directories(Win32ClassLib PUBLIC includes)
target_sources(Win32ClassLib PRIVATE pk.cpp)
