#include <iostream>
#include "util.h"
#include "cpk.h"
#include "minilzo/minilzo.h"

using namespace std;


//minilzo需要下面这堆东西
#define HEAP_ALLOC(var,size) \
    long __LZO_MMODEL var [((size)+(sizeof(long)-1))/sizeof(long)]
static HEAP_ALLOC(pLzoWorkMem, LZO1X_1_MEM_COMPRESS);

int main()
{
	const char * filename = "res/g78.cpk";
	Cpk cpk(filename);

	cpk.showHeadInfo();
 
	for(int i = 0; i < cpk.m_head.MaxItemNum; i ++)
		cpk.showItemInfo(i);


	Util::mkdir("out/ss");
	char data[256];
	strcpy(data, "hello world aaaaa bbbbb ccccc ddddd fffff jjjjj kkkkk lllll ;;;;; iiiii ddddd"
		"hello world aaaaa bbbbb ccccc ddddd fffff jjjjj kkkkk lllll ;;;;; iiiii ddddd"
		"hello world aaaaa bbbbb ccccc ddddd fffff jjjjj kkkkk lllll ;;;;; iiiii ddddd");

	char buff[256];
	int size;

	int ret = lzo1x_1_compress((lzo_byte*)data, strlen(data) + 1, (lzo_byte*)buff, (lzo_uint*)&size, pLzoWorkMem);
	cout << "compress " << ret << " " << size << endl;

	ofstream tt("out/ss/tt", ios::out|ios::binary);
	tt.write(buff, size);
	tt.close();

	char show[256];
	ifstream ss("out/ss/tt", ios::in|ios::binary);
	ss.read(show, size);
	ss.close();

	char finn[256];
	int outsize;
	ret = lzo1x_decompress((lzo_byte*)show, size, (lzo_byte*)finn, (lzo_uint*)&outsize, NULL);
	cout << "decompress " << ret << " " << outsize<< endl;
	cout << finn << endl;

	return 0;
}
 
