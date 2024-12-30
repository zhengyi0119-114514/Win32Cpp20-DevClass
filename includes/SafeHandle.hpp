#pragma once
#include "Def.h"
#include <windows.h>

namespace W32Cl::SafeHandles
{
class w32cl_api SafeHandle
{
  public:
    /**
     * @brief Construct a new Win32 Handle object
     *
     * @param hHandle
     */
    SafeHandle(HANDLE hHandle = NULL);
    /**
     * @brief Construct a new Win32 Handle object
     *
     * @param hHandle
     */
    SafeHandle(SafeHandle &&hHandle);
    /**
     * @brief Construct a new Safe Handle object
     *
     * @param hHandle
     */
    SafeHandle(CONST SafeHandle &hHandle);
    /**
     * @brief Cover to Win32 Handle
     *
     * @return HANDLE
     */
    operator HANDLE() const;
    /**
     * @brief Deref operator
     *
     * @return HANDLE*
     */
    HANDLE *operator&();
    /**
     * @brief Deref operator
     *
     * @return CONST HANDLE *
     */
    CONST HANDLE *operator&() CONST;
    /**
     * @brief
     *
     * @param rsh
     * @return SafeHandle&
     */
    SafeHandle &operator=(CONST SafeHandle &rsh);
    /**
     * @brief
     *
     * @param rsh
     * @return SafeHandle&
     */
    SafeHandle &operator=(SafeHandle &&rsh);
    /**
     * @brief swap
     *
     * @param rsh
     * @return VOID
     */
    VOID swap(SafeHandle &rsh) noexcept;
    BOOL operator==(CONST SafeHandle &rsh);

    virtual ~SafeHandle() noexcept;

  protected:
    virtual VOID CloseHandle();
    using date = struct
    {
        size_t sUseTime;
        HANDLE hHandle;
    };
    date *m_pDate = NULL;
};
VOID w32cl_api swap(SafeHandle &lsh, SafeHandle &rsh) noexcept;
} // namespace W32Cl::SafeHandles
