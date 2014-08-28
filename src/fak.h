#ifndef __FAK_H__
#define __FAK_H__

#include "define.h"
#include "vertex.h"
#include "material.h"


#pragma pack(4)
typedef struct _FakHead
{
    uint32      Lable;  // 类型标志
    uint32      Version;// 版本

//	uint32		vertType;

	uint32 		vertNum;

	uint32 		meshNum;
    uint32 		meshOffset;  
	
	uint32 		mtlNum;
    uint32 		mtlOffset;  
	
	uint32		frameNum;
	uint32		frameOffset;

	vec3		max;
	vec3		min;

	uint32		reserve[64];
	
} FakHead;



typedef struct _FakTri
{
	uint16 index[3];
} FakTri;

typedef struct _FakMesh
{
	uint16 baseIndex;
	int mtlId;
	uint16 vertNum;

	vec3 max;
	vec3 min;

	vector<FakTri> baseFaces;

	int lodNum;
	vector<FakTri> lodFaces[4];
} FakMesh;  

typedef struct _FakVert
{
	vec3	pos;
	vec3	normal;
	vec2	uv;
} FakVert;

typedef struct _FakNode
{
	uint32 tag;
	vec3 trans;
	quat rotat;
	bool mirror;
} FakNode;


typedef struct _FakFrame
{
	char name[5];
	float time;
	vector<FakVert> vertList;
	vector<FakNode> nodeList;
} FakFrame;



#pragma pack()


class Fak 
{
public:
	Fak(const char* filename);
	~Fak();

	void showHeadInfo();
	void showMaterialInfo();

	FakFrame readFakFrame(int i);
	FakMesh readFakMesh(int i);
	Material readMaterial(int i);
	FakNode readFakNode(int i);

public:
	char 	 m_path[255];
	ifstream m_file;

	FakHead m_head;

	vector<FakFrame> m_frameList;
	vector<FakMesh> m_meshList;
	vector<Material> m_mtlList;
	vector<FakNode> m_nodeList;
};



#endif //__SKIN_H__

