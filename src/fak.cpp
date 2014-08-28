#include "util.h"
#include "fak.h"


Fak::Fak(const char* filename)
{
	strcpy(m_path, filename);
	m_file.open(filename, ios::in|ios::binary);

	//read head
	memset(&m_head, 0, sizeof(m_head));
	m_file.seekg(0);
	m_file.read((char *)&m_head, sizeof(m_head));


	//read meshs	
	m_file.seekg(m_head.meshOffset);
	for(int i = 0; i < m_head.meshNum; i++)
		m_meshList.push_back(readFakMesh(i));
	cout << "read mesh finish: " << hex << showbase << m_file.tellg() << endl;
	//read frames
	m_file.seekg(m_head.frameOffset);
	for(int i = 0; i < m_head.frameNum; i++)
		m_frameList.push_back(readFakFrame(i));
	cout << "read frame finish: " << hex << showbase << m_file.tellg() << endl;


	//read material
	m_file.seekg(m_head.mtlOffset);
	for(int i = 0; i < m_head.mtlNum; i++)
		m_mtlList.push_back(readMaterial(i));
	cout << "read mtl finish: " << hex << showbase << m_file.tellg() << endl;
}


Fak::~Fak()
{
	m_file.close();
}


void Fak::showHeadInfo()
{
	cout << "=================================================" << endl;
	cout << "[Head]" << m_path << endl;
    cout << "Lable      " << hex << showbase << m_head.Lable       << endl; 
    cout << "Version    " << dec << showbase << (int)m_head.Version     << endl; 
    //cout << "vertType   " << dec << showbase << (int)m_head.vertType    << endl; 
    cout << "vertNum    " << dec << showbase << m_head.vertNum     << endl;  
    cout << "meshNum    " << dec << showbase << m_head.meshNum     << endl; 
    cout << "meshOffset " << hex << showbase << m_head.meshOffset  << endl; 
    cout << "frameNum   " << dec << showbase << m_head.frameNum << endl; 
    cout << "frameOffset " << hex << showbase << m_head.frameOffset  << endl; 
    cout << "mtlNum     " << dec << showbase << m_head.mtlNum      << endl; 
    cout << "mtlOffset  " << hex << showbase << m_head.mtlOffset   << endl; 
	cout << "=================================================" << endl;

}


FakFrame Fak::readFakFrame(int i)
{
	FakFrame t;
	m_file.read((char *)t.name, 4);
	m_file.read((char *)&t.time, sizeof(t.time));

	uint32 n;
	m_file.read((char *)&n, sizeof(n));
	for(int i = 0; i < n; i++)
	{
		FakVert tmp;
		m_file.read((char *)&tmp, sizeof(tmp));
		t.vertList.push_back(tmp);
	}

	m_file.read((char *)&n, sizeof(n));
	for(int i = 0; i < n; i++)
	{
		FakNode tmp;
		m_file.read((char *)&tmp, sizeof(tmp));
		t.nodeList.push_back(tmp);
	}

	return t;
}

FakMesh Fak::readFakMesh(int idx)
{
	FakMesh m;
	m_file.read((char *)&m.baseIndex, sizeof(m.baseIndex));
	m_file.read((char *)&m.mtlId, sizeof(m.mtlId));
	m_file.read((char *)&m.vertNum, sizeof(m.vertNum));
	m_file.read((char *)&m.max, sizeof(m.max));
	m_file.read((char *)&m.min, sizeof(m.min));

	uint32 n;
	m_file.read((char *)&n, sizeof(n));
	for(int i = 0; i < n; i++)
	{
		FakTri t;
		m_file.read((char *)&t, sizeof(t));
		m.baseFaces.push_back(t);
	}
	
	m_file.read((char *)&m.lodNum, sizeof(m.lodNum));
	for(int i = 0; i < 4; i++)
	{
		uint32 n;
		m_file.read((char *)&n, sizeof(n));
		for(int j = 0; j < n; j++)
		{
			FakTri t;
			m_file.read((char *)&t, sizeof(t));
			m.lodFaces[i].push_back(t);
		}
		if(n > 0)
			cout << "[LLLL]" << m_path << " lodNum " << i << " " << n <<endl;

	}

	cout << "[Fak]readFakMesh(" << idx << ") base:" << n << " lods: " << m.lodNum << endl;
	
	return m;
}

Material Fak::readMaterial(int i)
{
	cout << "[Fak]readMaterial(" << i << ")" << endl;
	Material m;
	m_file.read((char *)&m, sizeof(m));

 
	for(int t = 0; t < EMap_Max; t++)
	{
		if(strlen(m.map[t])>0 && t > 0)
			cout << "[TTTT]" << m_path << "map" << t << " "<<m.map[t] <<endl;
	}
	
	return m;
}


void Fak::showMaterialInfo()
{
	cout << "[MMMM]"<< m_path << endl;
	int cc = 0;
	for(int i = 0; i < m_mtlList.size(); i++)
	{
		for(int t = 0; t < EMap_Max; t++)
		{
			if(strlen(m_mtlList[i].map[t])>0)
				cc ++;
		}
	}
	cout << dec << "[MMMM]"<< cc << endl;

	for(int i = 0; i < m_mtlList.size(); i++)
	{
		for(int t = 0; t < EMap_Max; t++)
		{
			if(strlen(m_mtlList[i].map[t])>0)
				cout << "[MMMM]" << m_mtlList[i].map[t] <<endl;
		}
	}
}

FakNode Fak::readFakNode(int i)
{
	FakNode t;
	m_file.read((char *)&t, sizeof(t));
	return t;
}
