#include <windows.h>
#include "Def.h"
class wcl_api RemotePointer
{
	public:
	RemotePointer(DWORD dwProcessId ,size_t sMemSize,BOOL bAutoFree = TRUE); // TODO: 
	RemotePointer(HANDLE hProcess ,size_t sMemsize,BOOL bOpenProcess = TRUE,BOOL bAutoFree = TRUE); //TODO:
	RemotePointer(const RemotePointer&) = delete; //TODO:
	RemotePointer(RemotePointer&&);
	RemotePointer& operator =(CONST RemotePointer&) =delete; //TODO:
	RemotePointer&& operator =(RemotePointer&&);
	intptr_t GetNativePointerAddr() CONST;
	BOOL Write(PVOID pDate , size_t sDateSize);
	BOOL Read(PVOID pDate , size_t sDateSize) CONST;
	BOOL Free();
	BOOL IsNull() CONST;
	virtual ~RemotePointer();
	private:
	VOID _INIT(HANDLE hProcess ,size_t sMemSize , BOOL bAutoFree); //TODO:
	size_t m_sMemSize = 0;
	HANDLE m_hProcess = NULL;
	BOOL m_bFreeProcessHandle = FALSE;
	PVOID m_pAddr = NULL;
	BOOL m_bIsFree = FALSE;
};