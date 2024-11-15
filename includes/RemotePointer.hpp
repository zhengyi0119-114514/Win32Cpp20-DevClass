#pragma once
#include <minwindef.h>
#include <windows.h>
#include <winnt.h>
#include <cstdint>
#include "Def.h"

class w32cl_api RemotePointer
{
	public:
	RemotePointer(DWORD dwProcessId ,size_t sMemSize,
		intptr_t pBaseAddr=static_cast<intptr_t>(NULL) , BOOL bAutoFree = TRUE); // TODO: 
	RemotePointer(HANDLE hProcess ,size_t sMemsize, intptr_t pBaseAddr=static_cast<intptr_t>(NULL) 
		,BOOL bOpenProcess = TRUE,BOOL bAutoFree = TRUE); //TODO:
	RemotePointer(const RemotePointer&) = delete; //TODO:
	RemotePointer(RemotePointer&&);//TODO:
	RemotePointer& operator =(CONST RemotePointer&) =delete; //TODO:
	RemotePointer& operator =(RemotePointer&&);//TODO:
	intptr_t GetNativeRemotePointerAddr();//TODO:
	intptr_t GetLocalMappingPointer();//TODO:
	BOOL Free(); //TODO:
	PVOID operator*(); //TODO:
	BOOL _Push();//TODO:
	BOOL _Pull();//TODO:
	void swap(RemotePointer&);  //TODO:
	virtual ~RemotePointer();   //TODO:

	private:
	VOID _INIT(HANDLE hProcess ,size_t sMemSize,intptr_t pBaseAddr , BOOL bAutoFree); //TODO:
	BOOL _AllocMapMemory(); //TODO:



	size_t m_sMemSize = 0;
	HANDLE m_hProcess = NULL;
	BOOL m_bFreeProcessHandle = FALSE;
	PVOID m_pAddr = NULL;
	mutable PVOID m_pMemMap = NULL;
	BOOL m_bIsAddrFree = FALSE;
};
void w32cl_api swap(RemotePointer& lsh,RemotePointer& rsh); //TODO: