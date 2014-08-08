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
	static void fpath(const char* path, char* dest);
	static void fcopy(const char* path, const char* dest, bool delflag = false);
	static const char* guess(const char* data);
	static uint32 crc32(const char* pData, int nByteCount);

	static void trans(const char* dest);
};


#endif //__UTIL_H__

