#ifndef __MemoryLeakDetctor
#define __MemoryLeakDetctor

#pragma warning (disable : 4291)
#pragma warning (disable : 4345)
#include <crtdbg.h>
#include <cstdlib>
#include "MemoryTester.h"

#ifdef _DEBUG

inline void* operator new(size_t nSize, const char * lpszFileName, int nLine)
{
	void *ptr = malloc(nSize);
	MemTest::instance()->LogNew(ptr,lpszFileName,nSize,nLine);
    return ptr;
}

inline void operator delete(void *ptr)
{
	MemTest::instance()->LogDel(ptr);
	free(ptr);
}

#define DEBUG_NEW new(THIS_FILE, __LINE__)

//#define MALLOC_DBG(x) _malloc_dbg(x, 1, THIS_FILE, __LINE__);
//#define malloc(x) MALLOC_DBG(x)

#endif // _DEBUG

#endif // #include guard