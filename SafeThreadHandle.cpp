#include <utility>
#define w32cl_api __declspec(dllexport)
#include "Def.h"
#include "SafeThreadHandle.hpp"
#include <strsafe.h>
#include <windows.h>

namespace W32Cl::SafeHandles
{
DWORD SafeThreadHandle::GetExitCode() const
{
    DWORD dwExitCode = 0;
    ::GetExitCodeThread(ref_this.m_pDate->hHandle, &dwExitCode);
    return dwExitCode;
}
BOOL SafeThreadHandle::IsThreadExit() const
{
    return ref_this.GetExitCode() != STILL_ACTIVE;
}
DWORD SafeThreadHandle::GetThreadID() const
{
    return ::GetThreadId(ref_this.m_pDate->hHandle);
}
BOOL SafeThreadHandle::TerminateThread(UINT uExitCode)
{
    return ::TerminateThread(ref_this.m_pDate->hHandle, uExitCode);
}
DWORD SafeThreadHandle::GetThreadPriority() const
{
    return ::GetThreadPriority(ref_this.m_pDate->hHandle);
}
BOOL SafeThreadHandle::SetThreadPriority(INT iValue)
{
    return ::SetThreadPriority(ref_this.m_pDate->hHandle, iValue);
}
void SafeThreadHandle::swap(SafeThreadHandle &rsh)
{
    std::swap(ref_this.m_pDate, rsh.m_pDate);
}
void swap(SafeThreadHandle &lsh, SafeThreadHandle &rsh)
{
    lsh.swap(rsh);
}
} // namespace W32Cl::SafeHandles