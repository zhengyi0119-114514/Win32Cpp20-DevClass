find_package(Catch2 QUIET)

if(NOT Catch2_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0 # or a later release
    )
    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif()

include(CTest)
include(Catch)
target_link_libraries(test Catch2::Catch2WithMain)
set_target_properties(test
    PROPERTIES
    CXX_STANDARD 20
    C_STANDARD 17
)
