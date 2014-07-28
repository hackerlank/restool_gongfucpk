#include <iostream>
#include "util.h"
#include "cpk.h"
#include "minilzo/minilzo.h"

using namespace std;


int main()
{
	//const char * filename = "res/g78.cpk";
	const char * filename = "res/system.cpk";
	Cpk cpk(filename);

	cpk.showHeadInfo();
 
	for(int i = 0; i < cpk.m_head.MaxItemNum; i ++)
	{
		cpk.showItemInfo(i);
		cpk.writeItem(i);
	}
	

	return 0;
}
 
