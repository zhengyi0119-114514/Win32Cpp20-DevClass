#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <utility>
#include "includes/RemotePointer.hpp"
#include <memoryapi.h>
#include <windows.h>
#include <strsafe.h>

#define w32cl_api __declspec(dllexport)
#include "RemotePointer.hpp"

#define refthis (*this)



w32cl_api RemotePointer::RemotePointer(DWORD dwProcessId ,size_t sMemSize, intptr_t pBaseAddr , BOOL bAutoFree)
{
	refthis.m_hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ,FALSE, dwProcessId);
	if(refthis.m_hProcess == NULL)
	{
		return;
	}
	refthis.m_bFreeProcessHandle = TRUE;
	refthis._INIT(refthis.m_hProcess, sMemSize,pBaseAddr, bAutoFree);
}
w32cl_api RemotePointer::RemotePointer(HANDLE hProcess ,size_t sMemsize,intptr_t pBaseAddr,BOOL bOpenProcess,BOOL bAutoFree)
{
	if(m_bFreeProcessHandle)
	{
		PHANDLE phProcess = &refthis.m_hProcess;
		DuplicateHandle(GetCurrentProcess(), hProcess, GetCurrentProcess()
			,phProcess, 0, FALSE, DUPLICATE_SAME_ACCESS);
		refthis.m_bFreeProcessHandle = TRUE;
	}
	else 
	{
		refthis.m_hProcess = hProcess;
		refthis.m_bFreeProcessHandle = FALSE;
	}
	refthis._INIT(refthis.m_hProcess, sMemsize,pBaseAddr, bAutoFree);
}
VOID w32cl_api RemotePointer::_INIT(HANDLE hProcess ,size_t sMemSize ,intptr_t pBaseAddr, BOOL bAutoFree)
{
	refthis.m_sMemSize = sMemSize;
	refthis.m_pAddr = VirtualAllocEx(hProcess, (LPVOID)(pBaseAddr), (SIZE_T)sMemSize, MEM_COMMIT, PAGE_READWRITE);
	if(bAutoFree == FALSE)
	{
		refthis.m_bIsAddrFree = TRUE;
	}
	refthis._AllocMapMemory();
}
BOOL w32cl_api RemotePointer::Free()
{
	BOOL bOK = TRUE;
	if(refthis.m_bIsAddrFree == FALSE && refthis.m_pAddr != NULL)
	{
		if(!VirtualFreeEx(refthis.m_pAddr, refthis.m_pAddr,(SIZE_T)refthis.m_sMemSize, MEM_DECOMMIT))
		{
			bOK = FALSE;
		}
		refthis.m_pAddr = NULL;
	}
	if(refthis.m_bFreeProcessHandle && refthis.m_hProcess != NULL)
	{
		CloseHandle(refthis.m_hProcess);
		refthis.m_hProcess = NULL;
	}
	if(refthis.m_pMemMap != NULL)
	{
		free(refthis.m_pMemMap);
		refthis.m_pMemMap = std::nullptr_t();
		
	}
	return bOK;
}
PVOID w32cl_api RemotePointer::operator*() 
{ 
	refthis._AllocMapMemory();
	return refthis.m_pMemMap;
}
w32cl_api RemotePointer::~RemotePointer()
{
	refthis.Free();
}
BOOL w32cl_api RemotePointer::_AllocMapMemory() 
{
	if (refthis.m_pAddr!=0)
	{
		refthis.m_pAddr = malloc(refthis.m_sMemSize);
		if(refthis.m_pAddr ==NULL) {return FALSE;}
	}
	return TRUE;
}
void w32cl_api RemotePointer::swap(RemotePointer& r)
{
	std::swap(refthis.m_bFreeProcessHandle, r.m_bFreeProcessHandle);
	std::swap(refthis.m_bIsAddrFree	,r.m_bIsAddrFree);
	std::swap(refthis.m_hProcess	,r.m_hProcess);
	std::swap(refthis.m_pAddr		,r.m_pAddr);
	std::swap(refthis.m_pMemMap		,r.m_pMemMap);
}

void w32cl_api swap(RemotePointer& l,RemotePointer r)
{
	l.swap(r);
}
intptr_t w32cl_api RemotePointer::GetNativeRemotePointerAddr()
{
	return (intptr_t)refthis.m_pAddr;
}
intptr_t w32cl_api RemotePointer::GetLocalMappingPointer()
{
	return (intptr_t)(*refthis);
}

w32cl_api RemotePointer::RemotePointer(RemotePointer&& r)
{
	refthis.swap(r);
}
w32cl_api RemotePointer& RemotePointer::operator =(RemotePointer&& rsl)
{
	RemotePointer cp(std::move(rsl));
	refthis.swap(cp);
	return refthis;
}
BOOL w32cl_api RemotePointer::_Push()
{
	BOOL bOK =FALSE;
	bOK = WriteProcessMemory(refthis.m_hProcess,*refthis,refthis.m_pMemMap,refthis.m_sMemSize,NULL);
	return bOK;
}
BOOL w32cl_api RemotePointer::_Pull()
{
	BOOL bOK =FALSE;
	bOK = ReadProcessMemory(refthis.m_hProcess,refthis.m_pAddr,*refthis,refthis.m_sMemSize,NULL);
	return bOK;
}