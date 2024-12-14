#include <catch2/catch_all.hpp>
#include <processthreadsapi.h>
#include <windows.h>
#include "SafeHandle.hpp"

TEST_CASE("TestCatch2", "[w32_lib]")
{
    using namespace W32Cl::SafeHandles;
    SafeHandle handle {};
    
}