#include <iostream>
#include "cpk.h"

using namespace std;




int main()
{
	const char * filename = "res/g78.cpk";
	Cpk cpk(filename);
	cpk.showHeadInfo();
 
	for(int i = 0; i < cpk.m_head.FileNum; i ++)
		cpk.showItemInfo(i);

	return 0;
}
 
