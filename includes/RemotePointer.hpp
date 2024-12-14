#pragma once
#include "Def.h"
#include "SafeHandle.hpp"
#include <windows.h>

namespace W32Cl::Pointers
{
class w32cl_api RemotePointer
{
  public:
  private:
    W32Cl::SafeHandles::SafeHandle m_hProcess{NULL};
};
} // namespace W32Cl::Pointers
