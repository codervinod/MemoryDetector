#ifndef __VINOD_MEMORY_TESTER__
#define __VINOD_MEMORY_TESTER__
#include <string>
#include <map>
#include <windows.h>
typedef std::map<unsigned long,std::string> MemMapType;

class MemTest
{
public:
	void LogNew(void *ptr,std::string fileName,int nSize,int lineNum);
	void LogDel(void *ptr);
	void DumpMap();
	static MemTest *instance();
private:
	MemTest();
	static MemTest *__inst;
	MemMapType m_MemMap;
	CRITICAL_SECTION m_CS;
};

#endif
