#ifndef _MODELLISTCLASS_H_ 
#define _MODELLISTCLASS_H_

#include <d3d11.h>
#include<stdlib.h>
#include<time.h>
#include<xnamath.h>


class ModelListClass{
private:
	struct ModelInfoType{
		XMFLOAT4 color;
		float positionX, positionY, positionZ;
	};

public:
	ModelListClass();
	ModelListClass(const ModelListClass&);
	~ModelListClass();

	bool Initialize(int);
	void Shutdown();

	int GetModelCount();
	void GetData(int, float&, float&, float&, XMVECTOR&);

private:
	int m_modelCount;
	ModelInfoType* m_ModelInfoList;

};



#endif