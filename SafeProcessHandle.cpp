#define w32cl_api __declspec(dllexport)
#include "SafeProcessHandle.hpp"
#include "Def.h"
#include <strsafe.h>
#include <windows.h>


namespace W32Cl::SafeHandles
{
UINT ProcessHandle::GetExitCode() const
{
    return get_exit_code();
}
unsigned ProcessHandle::get_exit_code() const
{
    DWORD dwExitCode = 0;
    GetExitCodeProcess(ref_this.m_pDate->hHandle, &dwExitCode);
    return dwExitCode;
}
BOOL ProcessHandle::TerminateProcess(UINT fuExitCode)
{
    return ::TerminateProcess(ref_this.m_pDate->hHandle, fuExitCode);
}
BOOL ProcessHandle::terminate_process(unsigned fuExitCode)
{
    return ref_this.TerminateProcess(fuExitCode);
}
VOID ProcessHandle::WaitToProcessExit() const
{
    WaitForSingleObject(ref_this.m_pDate->hHandle, INFINITE);
}
BOOL ProcessHandle::IsProcessExit() const
{
    return ref_this.GetExitCode() == STILL_ACTIVE;
}
BOOL ProcessHandle::SetPriorityClass(DWORD dwFlag)
{
    return ::SetPriorityClass(ref_this.m_pDate->hHandle, dwFlag);
}
DWORD ProcessHandle::GetPriorityClass() const
{
    return ::GetPriorityClass(ref_this.m_pDate->hHandle);
}
BOOL ProcessHandle::GetProcessPriorityBoost() CONST
{
    BOOL bProcessPriorityBoost = FALSE;
    ::GetProcessPriorityBoost(ref_this.m_pDate->hHandle, &bProcessPriorityBoost);
    return bProcessPriorityBoost;
}
BOOL ProcessHandle::SetProcessPriorityBoost(BOOL bProcessPriorityBoost)
{
    return ::SetProcessPriorityBoost(ref_this.m_pDate->hHandle, bProcessPriorityBoost);
}
DWORD ProcessHandle::GetProcessID() const
{
    return ::GetProcessId(ref_this.m_pDate->hHandle);
}
} // namespace W32Cl::SafeHandles