#include <iostream>
#include "util.h"
#include "cpk.h"
#include "skel.h"
#include "skin.h"
#include "minilzo/minilzo.h"

using namespace std;


void read_cpk(const char *filename)
{
	Cpk cpk(filename);

	cpk.showHeadInfo();
 
	for(int i = 0; i < cpk.m_head.MaxItemNum; i ++)
	{
		cpk.showItemInfo(i);
		cpk.writeItem(i);
	}
	
}


void read_skel(const char *filename)
{
	Skel skel(filename);

	skel.showHeadInfo();

}

void read_skin(const char *filename)
{
	Skin skin(filename);

	//skin.showHeadInfo();
	skin.showMaterialInfo();
}
 
int main(int argc, char* argv[])
{
	//read_cpk("res/cpk/g78.cpk");
	//read_cpk("res/cpk/system.cpk");
	
	//read_skel("res/skel/6779ED9F.skel");
	
	//read_skin("res/skin/F569E90.skin");

	//for(int i = 1; i < argc; i ++)
	//	read_skin(argv[i]);
	
	//const char * dir = "system\\boot";
	//cout << hex << showbase << Util::crc32(dir, strlen(dir)) << endl;
	//const char * str = "system\\boot\\fx28.dds";
	//cout << hex << showbase << Util::crc32(str, strlen(str)) << endl;
	

	Util::trans("out/res/");

	return 0;
}
