#include "stdafx.h"


class CSystemInfo : public SYSTEM_INFO
{
public:
	CSystemInfo() { GetSystemInfo(this); }
};

#ifdef __VM_0819
CHeapMng::CHeapMng(const char* szHeap)
	: m_nAlloc(0),
	m_nTotal(0)
#else	// __VM_0819
CHeapMng::CHeapMng()
#endif	// __VM_0819
{
#ifdef __VM_0819
	strcpy(m_szHeap, szHeap);
#endif	// __VM_0819
	CSystemInfo si;
	m_hHeap = HeapCreate(0, si.dwPageSize, 0);
#ifdef __VM_0819
	InitializeCriticalSectionAndSpinCount(&m_cs, 2000);
#endif // __VM_0819
}

CHeapMng::~CHeapMng()
{
	HeapDestroy(m_hHeap);
#ifdef __VM_0819
	DeleteCriticalSection(&m_cs);
#endif // __VM_0819
}

void* CHeapMng::Malloc(size_t nSize)
{
#ifdef __VM_0819
	EnterCriticalSection(&m_cs);
	m_nAlloc++;
	m_nTotal += nSize;
#endif	// __VM_0819
	LPVOID lpMem = HeapAlloc(m_hHeap, 0, nSize);
#ifdef __VM_0819
	LeaveCriticalSection(&m_cs);
#endif __VM_0819
	return lpMem;
}

#ifdef __VM_0819
void CHeapMng::Free(LPVOID lpMem, size_t nSize)
#else	// __VM_0819
void CHeapMng::Free(LPVOID lpMem)
#endif	// __VM_0819
{
#ifdef __VM_0819
	EnterCriticalSection(&m_cs);
	m_nAlloc--;
	m_nTotal -= nSize;
#endif	// __VM_0819
	HeapFree(m_hHeap, 0, lpMem);
#ifdef __VM_0819
	LeaveCriticalSection(&m_cs);
#endif // __VM_0819
}

void* CHeapMng::Realloc(LPVOID lpMem, size_t nSize)
{
	LPVOID lpNewMem = HeapReAlloc(m_hHeap, 0, lpMem, nSize);
	return lpNewMem;
}