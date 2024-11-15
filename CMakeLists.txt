cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
project(Win32Cpp20DevClassLib CXX C)

add_library(Win32ClassLib SHARED)
add_executable(unit_test)

find_package(Catch2 REQUIRED)
target_link_libraries(unit_test PUBLIC  Catch2::Catch2WithMain Win32ClassLib)
target_sources(unit_test PRIVATE test/test.cpp)

if(MSVC)
	target_compile_options(Win32ClassLib PRIVATE "/utf-8")
endif()


target_include_directories(Win32ClassLib  PUBLIC includes )
target_sources(Win32ClassLib  PRIVATE pk.cpp)

set_target_properties(Win32ClassLib 
	PROPERTIES 
	CXX_STANDARD_REQUIRED 20
	CXX_EXTENSIONS FALSE)
