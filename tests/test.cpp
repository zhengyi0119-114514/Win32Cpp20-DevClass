#include <catch2/catch_all.hpp>
#include <processthreadsapi.h>
#include <windows.h>
#include "SafeHandle.hpp"
#include "SafeProcessHandle.hpp"

TEST_CASE("TestCatch2", "[w32_lib]")
{
    using namespace W32Cl::SafeHandles;
    ProcessHandle hProcess{GetCurrentProcess()};
    REQUIRE(!hProcess.IsProcessExit());
}
TEST_CASE("ProcessHandleTest","[w32_lib]")
{
    REQUIRE(TRUE);
}