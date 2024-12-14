cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
project(Win32Cpp20DevClassLib CXX C)

add_library(Win32ClassLib SHARED)

# add_subdirectory(test)
if(MSVC)
    target_compile_options(Win32ClassLib PRIVATE "/utf-8")
endif()

target_include_directories(Win32ClassLib PUBLIC includes)
target_sources(Win32ClassLib PRIVATE
    RemotePointer.cpp
    SafeHandle.cpp
    SafeProcessHandle.cpp
)

set_target_properties(Win32ClassLib
    PROPERTIES
    CXX_STANDARD_REQUIRED 20
    CXX_EXTENSIONS FALSE
)
add_executable(test test/test.cpp)
add_subdirectory(test)
catch_discover_tests(test)
target_link_libraries(test Win32ClassLib)