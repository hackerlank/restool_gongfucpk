#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;

class Util
{
public:
	static bool mkdir(const char* path);

};


#endif //__UTIL_H__

