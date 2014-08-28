#include <iostream>
#include "minilzo/minilzo.h"
#include "util.h"
#include "cpk.h"
#include "skel.h"
#include "skin.h"
#include "smm.h"
#include "fak.h"

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

	skin.showHeadInfo();
	//skin.showMaterialInfo();
}

void read_smm(const char *filename)
{
	Smm smm(filename);
	smm.showHeadInfo();
	//smm.showMaterialInfo();
}
	
void read_fak(const char *filename)
{
	Fak fak(filename);
	fak.showHeadInfo();
	fak.showMaterialInfo();
}

 
int main(int argc, char* argv[])
{
	//read_cpk("res/cpk/g78.cpk");
	//read_cpk("../system.cpk");
	
	//read_skel("res/skel/6779ED9F.skel");
	//for(int i = 1; i < argc; i ++)
	//	read_skel(argv[i]);
	
	//read_skin("res/skin/F569E90.skin");
	//for(int i = 1; i < argc; i ++)
	//	read_skin(argv[i]);
	
	//read_smm("res/smm/64212A26.smm");
	//for(int i = 1; i < argc; i ++)
	//	read_smm(argv[i]);
	
	//read_fak("res/fak/28F76578.fak");
	//read_fak("res/fak/54637E6.fak");
	//for(int i = 1; i < argc; i ++)
	//	read_fak(argv[i]);
	

	//const char * dir = "system\\weapon\\quan";
	//cout << hex << showbase << Util::crc32(dir, strlen(dir)) << endl;
	//const char * str = "system\\weapon\\quan\\z08.fsm";
	//cout << hex << showbase << Util::crc32(str, strlen(str)) << endl;
	

	//Util::transSkin("out/");
	//Util::transSkel("out/");
	//Util::transSmm("out/");
	Util::transFak("out/");

	return 0;
}
