
#include <iostream>
#include <utility>
#define w32cl_api __declspec(dllexport)
#include "Def.h"
#include "SafeHandle.hpp"

namespace W32Cl::SafeHandles
{
SafeHandle::SafeHandle(HANDLE hHandle)
{
    ref_this.m_pDate = (SafeHandle::date *)malloc(sizeof(SafeHandle::date));
    ref_this.m_pDate->hHandle = hHandle;
    ref_this.m_pDate->sUseTime = 0 + 1;
}
SafeHandle::SafeHandle(SafeHandle &&hHandle)
{
    ref_this.swap(hHandle);
}
SafeHandle::SafeHandle(CONST SafeHandle &h)
{
    ref_this.m_pDate = h.m_pDate;
    ref_this.m_pDate->sUseTime++;
}
SafeHandle &SafeHandle::operator=(const SafeHandle &rsh)
{
    SafeHandle handle{rsh};
    ref_this.swap(handle);
    return_ref_this;
}
SafeHandle &SafeHandle::operator=(SafeHandle &&rsh)
{
    ref_this.swap(rsh);
    return_ref_this;
}
HANDLE *SafeHandle::operator&()
{
    return const_cast<HANDLE *>(std::as_const(ref_this).operator&());
}
CONST HANDLE *SafeHandle::operator&() const
{
    return &(ref_this.m_pDate->hHandle);
}
VOID SafeHandle::swap(SafeHandle &r) noexcept
{
    std::swap(ref_this.m_pDate, r.m_pDate);
}
SafeHandle::~SafeHandle() noexcept
{
    ref_this.CloseHandle();
}
VOID SafeHandle::CloseHandle()
{
    ref_this.m_pDate->sUseTime--;

    if (ref_this.m_pDate == 0)
    {
        ::CloseHandle(ref_this.m_pDate->hHandle);
        ref_this.m_pDate->hHandle = 0;
        free((PVOID)ref_this.m_pDate);
        ref_this.m_pDate = NULL;
        std::cout<<"Handle Free"<<std::endl;
    }
}//7/
VOID w32cl_api swap(SafeHandle &lsh, SafeHandle &rsh) noexcept
{
    lsh.swap(rsh);
}
BOOL SafeHandle::operator==(const SafeHandle &rsh)
{
    return ref_this.m_pDate->hHandle == rsh.m_pDate->hHandle;
}
} // namespace W32Cl::SafeHandles