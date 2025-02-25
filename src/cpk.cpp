#include "util.h"
#include "cpk.h"
#include "minilzo/minilzo.h"


Cpk::Cpk(const char* filename)
{
	strcpy(m_path, filename);
	m_file.open(filename, ios::in|ios::binary);

	memset(&m_head, 0, sizeof(m_head));
	m_file.seekg(0);
	m_file.read((char *)&m_head, sizeof(m_head));

	m_item = new CpkItem[m_head.MaxItemNum];
	m_file.seekg(m_head.ItemStart);
	m_file.read((char *)m_item, sizeof(CpkItem) * m_head.MaxItemNum);

}


Cpk::~Cpk()
{
	m_file.close();
}


void Cpk::showHeadInfo()
{
	cout << "=================================================" << endl;
	cout << "[Head]" << m_path << endl;
    cout << "Lable         " << hex << showbase << m_head.Lable        << endl; // 类型标志
    cout << "Version       " << dec << showbase << m_head.Version      << endl; // 版本
    cout << "ItemStart     " << dec << showbase << m_head.ItemStart    << endl; // 文件表起始字节
    cout << "DataStart     " << dec << showbase << m_head.DataStart    << endl; // 数据块起始地址
    cout << "FileNum       " << dec << showbase << m_head.FileNum      << endl; // 当前文件个数 
    cout << "IsFormatted   " << dec << showbase << m_head.IsFormatted  << endl; // 文件是否被整理过
    cout << "SizeOfHead    " << dec << showbase << m_head.SizeOfHead   << endl; // 文件头大小
    cout << "ValidItemNum  " << dec << showbase << m_head.ValidItemNum << endl; // 有效Table项个数，包括有效文件和碎片
    cout << "MaxItemNum    " << dec << showbase << m_head.MaxItemNum   << endl; // 最大Table项个数
    cout << "FragmentNum   " << dec << showbase << m_head.FragmentNum  << endl; // 碎片数目，应该为dwValidTableNum - dwFileNum
    cout << "PackageSize   " << dec << showbase << m_head.PackageSize  << endl; // 当前包大小
	cout << "=================================================" << endl;

}

void Cpk::showItemInfo(int index)
{
	CpkItem cc = m_item[index];
	if(cc.OriginSize == 0 || cc.PackedSize == 0)
		return;

	cout << "-------------------------------------------------" << endl;
	cout << "[Item] [" << index << "] ";
    if(IS_FILE(cc.Flag))
	{
		cout << "Type is File" << endl;
	}else
	{
		if(IS_DIR(cc.Flag))
			cout << "Type is Dir" << endl;
		else
			cout << "Type is UnKnown" << endl;
	}

    cout << "CRC            " << hex << showbase << cc.CRC           << endl;  // CRC较验
    cout << "Flag           " << hex << showbase << cc.Flag          << endl;  // 标志
    cout << "FatherCRC      " << hex << showbase << cc.FatherCRC     << endl;  // 父目录CRC
    cout << "StartPos       " << dec << showbase << cc.StartPos      << endl;  // 开始位置
    cout << "PackedSize     " << dec << showbase << cc.PackedSize    << endl;  // 压缩后长度
    cout << "OriginSize     " << dec << showbase << cc.OriginSize    << endl;  // 原文件长度
    cout << "ExtraInfoSize  " << dec << showbase << cc.ExtraInfoSize << endl;  // 附加信息长度
    cout << "EFMT           " << dec << showbase << GET_EFMT(cc.Flag)<< endl;  // 压缩加密方法
	
	cout << "-------------------------------------------------" << endl;
}




void Cpk::writeItem(int index)
{
	CpkItem cc = m_item[index];
	if(IS_DEL(cc.Flag) || cc.OriginSize == 0 || cc.PackedSize == 0)
		return;

	char dirpath[255];
	char outpath[255];

	sprintf(dirpath, "out/%s/%X/", m_path, cc.FatherCRC);
	sprintf(outpath, "out/%s/%X/%X", m_path, cc.FatherCRC, cc.CRC);


	Util::mkdir(dirpath);

	char * data = new char[cc.PackedSize];

	m_file.seekg(cc.StartPos);
	m_file.read(data, cc.PackedSize);

	if(GET_EFMT(cc.Flag) == EFMT_MiniLzo)
	{
		int size = 0;
		char * buff = new char[cc.OriginSize];
		int ret = lzo1x_decompress((lzo_byte*)data, cc.PackedSize, (lzo_byte*)buff, (lzo_uint*)&size, NULL);
		if(ret == LZO_E_OK && size == cc.OriginSize)
		{
			const char* ext = Util::guess((const char*)buff);
			strcat(outpath, ext);
			cout << "[WRITE] [" << index << "] " << outpath << endl;
			ofstream out(outpath, ios::out|ios::binary);
			out.write(buff, size);
			out.close();
		}else
		{
			cout << "[CPK]writeItem: Lzo Decompress Failed For " << outpath << "(" << size << "/" << cc.OriginSize << ")" << endl;
		}
		delete []buff;
	}else if(GET_EFMT(cc.Flag) == EFMT_None)
	{
		const char* ext = Util::guess((const char*)data);
		strcat(outpath, ext);
		cout << "[WRITE] [" << index << "] " << outpath << endl;
		ofstream out(outpath, ios::out|ios::binary);
		out.write(data, cc.PackedSize);
		out.close();
	}

	delete []data;
 
}
