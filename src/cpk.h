#ifndef __CPK_H__
#define __CPK_H__

#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;


typedef signed char         int8;
typedef short               int16;
typedef int                 int32;

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;

#pragma pack(4)
typedef struct _CpkHead
{
    uint32 Lable;        // 类型标志
    uint32 Version;      // 版本
    uint32 ItemStart;    // 文件表起始字节
    uint32 DataStart;    // 数据块起始地址
    uint32 FileNum;      // 当前文件个数 
    uint32 IsFormatted;  // 文件是否被整理过
    uint32 SizeOfHead;   // 文件头大小
    uint32 ValidItemNum; // 有效Table项个数，包括有效文件和碎片
    uint32 MaxItemNum;   // 最大Table项个数
    uint32 FragmentNum;  // 碎片数目，应该为dwValidTableNum - dwFileNum
    uint32 PackageSize;  // 当前包大小
    uint32 Reserved[20];
} CpkHead;

typedef struct _CpkItem
{
    uint32 CRC;              // CRC较验
    uint32 Flag;             // 标志
    uint32 FatherCRC;        // 父目录CRC
    uint32 StartPos;         // 开始位置
    uint32 PackedSize;       // 压缩后长度
    uint32 OriginSize;       // 原文件长度
    uint32 ExtraInfoSize;    // 附加信息长度
} CpkItem;  


typedef struct _CpkFile
{
	CpkItem* pTableItem;    // 指向索引表

	// memory
	void* lpMapAddress;   // Map开始位置
	void* lpStartAddress; // Map中的文件开始位置
	uint32 Offset;       // 实际Map起始地址与文件开始地址的偏差
	void* lpMem;          // 指向文件实际内容

	// for seek/tell
	uint32 FileSize;     // 文件实际内容大小
	uint32 Pointer;      // 文件指针
	
	bool isCompressed;    // 文件是否被压缩
	bool isValid;         // 是否有效
} CpkFile;


#pragma pack()

enum EFMT
{
	EFMT_Null,

	//各种数据压缩算法
	EFMT_None,
	EFMT_MiniLzo,
	EFMT_ZLib,
	EFMT_ZLibDeflated,

	//各种加密解密散列算法
	EFMT_Des,
	EFMT_Ras,
	EFMT_Md5,
	EFMT_Sha1,
	EFMT_Sha512,

	EFMT_End
};


#define IS_FILE(f)		((f) & 0x00000001)
#define IS_DIR(f)		((f) & 0x00000002)
#define IS_BIG(f)		((f) & 0x00000004)

#define GET_EFMT(f)		((f) & 0xffff0000)


class Cpk
{
public:
	Cpk(const char* filename);
	~Cpk();

	void showHeadInfo();
	void showItemInfo(int index);

public:
	char 	 m_path[255];
	ifstream m_file;

	CpkHead  m_head;
	CpkItem* m_item;

};



#endif //__CPK_H__

