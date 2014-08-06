#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include "define.h"
using namespace std;

class Util
{
public:
	static bool mkdir(const char* path);
	static const char* guess(const char* data);
	static uint32 crc32(const char* pData, int nByteCount);

};


#endif //__UTIL_H__

