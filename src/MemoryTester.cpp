#include "umremovemsvcwarning.h"
#include "MemoryTester.h"
#include <fstream.h>
#include <string>
#include <map>

void MemTest::LogNew(void *ptr,std::string fileName,int nSize,int lineNum)
{
	char location[512];

	EnterCriticalSection(&m_CS);
	sprintf(location,"%s ,Size:%d, at location %d",fileName.c_str(),nSize,lineNum);
	std::string CatName(location);
	m_MemMap.insert(MemMapType::value_type((unsigned long)ptr,CatName));
	LeaveCriticalSection(&m_CS);
}

void MemTest::LogDel(void *ptr)
{
	MemMapType::iterator itr;

	EnterCriticalSection(&m_CS);

	itr = m_MemMap.find((unsigned long)ptr);
	if(itr != m_MemMap.end())
	{
		m_MemMap.erase(itr);
	}

	LeaveCriticalSection(&m_CS);
}

void MemTest::DumpMap()
{
	ofstream outFile("c:\\memLog.txt",ios::app);
	MemMapType::iterator itr;

	EnterCriticalSection(&m_CS);

	outFile<<"Beginning Memory Leak Dump....\n";

	itr = m_MemMap.begin();

	while(itr != m_MemMap.end())
	{
		outFile<<"Memory leaked from "<<(*itr).second.c_str()<<"line at 0x"<<(*itr).first<<endl;
		++itr;
	}

	LeaveCriticalSection(&m_CS);
}

MemTest::MemTest()
{
	//Lets cleaer the file
	ofstream outFile("c:\\memLog.txt");
	InitializeCriticalSection(&m_CS);
}

MemTest *MemTest::instance()
{
	if(!__inst)
	{
		__inst =new MemTest;
	}

	return __inst;
}

MemTest *MemTest::__inst = NULL;

