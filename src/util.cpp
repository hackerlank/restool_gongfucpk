#include "util.h"

bool Util::mkdir(const char *path)
{  
	char DirName[256];  
	strcpy(DirName, path);  

	int len = strlen(DirName);  
	
	if(DirName[len-1] != '/')
		strcat(DirName,   "/");  

	len = strlen(DirName);  

	for(int i = 1; i<len; i++)  
	{  
		if(DirName[i]=='/')  
		{  
			DirName[i] = 0;  
			if(access(DirName, 0) != 0)  
			{  
				if(::mkdir(DirName, 0755) == -1)  
				{   
					cout << "[Util]mkdir failed: " << DirName << endl;
					return false;   
				}
			}
			DirName[i] = '/';  
		} 
	} 
	
	return true;  
}  


const char* Util::guess(const char *data)
{
	//MAGIC
	//AKK-SKEL-SKIN
	//SMM-SCN-NAV-GMB
	//DDS->DDS
	//BMP->BM
	//JPG->0xd8ff
	static const char *TagList[11] = {"SKEL", "SKIN", "AKK", "QTD", "SMM", "SCN", "NAV", "GMB", "TRN", "DDS", "BM"};
	static const char *ExtList[11] = {".skel", ".skin", ".fak", ".qtd", ".smm", ".scn", ".nav", ".gmb", ".trn", ".dds", ".bmp"};

	for(int i = 0; i < 11; i ++)
	{
		bool flag = true;
		const char *tag = TagList[i];
		for(int j = 0; j < strlen(tag); j ++)
		{
			if(data[j] != tag[j])
			{
				flag = false;
				break;
		    }
		}

		if(flag)
			return ExtList[i];

	}

	if(data[0] == (char)0xff && data[1] == (char)0xd8)
		return ".jpg";

	if(data[0] == (char)0x00 && data[1] == (char)0x00)
		return ".tga";

	return "";
}

