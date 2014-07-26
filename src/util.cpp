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
