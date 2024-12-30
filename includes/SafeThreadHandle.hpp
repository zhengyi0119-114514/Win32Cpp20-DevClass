#pragma once
#include "Def.h"
#include "SafeHandle.hpp"
#include <windows.h>
namespace W32Cl::SafeHandles
{
class w32cl_api SafeThreadHandle : SafeHandle
{
  public:
    using SafeHandle::SafeHandle;
    using SafeHandle::operator HANDLE;
    using SafeHandle::operator&;
    using SafeHandle::operator=;
    DWORD GetExitCode() const;
    BOOL IsThreadExit() const;
    DWORD GetThreadPriority() const;
    BOOL SetThreadPriority(INT iValue);
    DWORD GetThreadID() const;
    BOOL TerminateThread(UINT uExitCode);
    void join();
    void swap(SafeThreadHandle &rsh);
};
void swap(SafeThreadHandle &lsh, SafeThreadHandle &rsh);
} // namespace W32Cl::SafeHandles