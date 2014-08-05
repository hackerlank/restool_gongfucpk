#include <iostream>
#include "util.h"
#include "cpk.h"
#include "skel.h"
#include "minilzo/minilzo.h"

using namespace std;


void read_cpk()
{
	//const char * filename = "res/cpk/g78.cpk";
	const char * filename = "res/cpk/system.cpk";
	Cpk cpk(filename);

	cpk.showHeadInfo();
 
	for(int i = 0; i < cpk.m_head.MaxItemNum; i ++)
	{
		cpk.showItemInfo(i);
		cpk.writeItem(i);
	}
	
}


void read_skel()
{
	const char * filename = "res/skel/6779ED9F.skel";
	Skel skel(filename);

	skel.showHeadInfo();

}
 
int main()
{
	//read_cpk();
	read_skel();
	return 0;
}
