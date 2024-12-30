#pragma once
#include "Def.h"
#include "SafeHandle.hpp"
#include <windows.h>

namespace W32Cl::SafeHandles
{
class w32cl_api ProcessHandle : public SafeHandle
{
  public:
    using SafeHandle::SafeHandle;
    using SafeHandle::operator HANDLE;
    using SafeHandle::operator&;
    using SafeHandle::operator=;
    /**
     * @brief Get the Exit Code
     * 
     * @return UINT 
     */
    UINT GetExitCode() const;
    /**
     * @brief Get the exit code 
     * 
     * @return unsigned 
     */
    unsigned get_exit_code() const;
    /**
     * @brief Close process
     * 
     * @param fuExitCode 
     * @return BOOL 
     */
    BOOL TerminateProcess(UINT fuExitCode);
    /**
     * @brief Close process
     * 
     * @param fuExitCode 
     * @return BOOL 
     */
    BOOL terminate_process(unsigned fuExitCode);
    /**
     * @brief Wait to exit
     * 
     * @return VOID 
     */
    VOID WaitToProcessExit() const;
    BOOL IsProcessExit() const;
    BOOL SetPriorityClass(DWORD dwFlag);
    BOOL SetProcessPriorityBoost(BOOL bDisablePriorityBoost);
    BOOL GetProcessPriorityBoost() CONST;
    DWORD GetPriorityClass() const;
    DWORD GetProcessID() const;

  protected:
};

using process_handle = SafeHandles::ProcessHandle;
} // namespace W32Cl::SafeHandles