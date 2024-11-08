#define wcl_api __declspec(dllexport)
#include <windows.h>
#include <strsafe.h>

#include "RemotePointer.hpp"
#define refthis (*this)



RemotePointer::RemotePointer(DWORD dwProcessId ,size_t sMemSize , BOOL bAutoFree)
{
	refthis.m_hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ,FALSE, dwProcessId);
	if(refthis.m_hProcess == NULL)
	{
		return;
	}
	refthis.m_bFreeProcessHandle = TRUE;
	refthis._INIT(refthis.m_hProcess, sMemSize, bAutoFree);
}
RemotePointer::RemotePointer(HANDLE hProcess ,size_t sMemsize,BOOL bOpenProcess,BOOL bAutoFree)
{
	if(m_bFreeProcessHandle)
	{
		PHANDLE phProcess = &refthis.m_hProcess;
		DuplicateHandle(GetCurrentProcess(), hProcess, GetCurrentProcess()
			,phProcess, NULL, FALSE, DUPLICATE_SAME_ACCESS);
		refthis.m_bFreeProcessHandle = TRUE;
	}
	else 
	{
		refthis.m_hProcess = hProcess;
		refthis.m_bFreeProcessHandle = FALSE;
	}
	refthis._INIT(refthis.m_hProcess, sMemsize, bAutoFree);
}
VOID RemotePointer::_INIT(HANDLE hProcess ,size_t sMemSize , BOOL bAutoFree)
{
	refthis.m_sMemSize = sMemSize;
	refthis.m_pAddr = VirtualAllocEx(hProcess, NULL, (SIZE_T)sMemSize, MEM_COMMIT, PAGE_READWRITE);
	if(bAutoFree == FALSE)
	{
		refthis.m_bIsFree = TRUE;
	}
}

BOOL RemotePointer::Free()
{
	BOOL bOK = TRUE;
	if(refthis.m_bIsFree == FALSE && refthis.m_pAddr != NULL)
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
	return bOK;
}
