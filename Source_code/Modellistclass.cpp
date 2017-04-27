#include "../Header_file/Modellistclass.h"

ModelListClass::ModelListClass(){

	m_ModelInfoList = 0;
}

ModelListClass::ModelListClass(const ModelListClass&){


}

ModelListClass::~ModelListClass(){

}

bool ModelListClass::Initialize(int numModels){
	int i;
	float red, green, blue;

	m_modelCount = numModels;

	m_ModelInfoList = new ModelInfoType[m_modelCount];
	if (!m_ModelInfoList){
		return false;
	}

	srand((unsigned int)time(NULL));

	for (i = 0; i < m_modelCount; i++){
		red = (float)rand() / RAND_MAX;
		green = (float)rand() / RAND_MAX;
		blue = (float)rand() / RAND_MAX;

		m_ModelInfoList[i].color.x=red;
		m_ModelInfoList[i].color.y = green;
		m_ModelInfoList[i].color.z = blue;
		m_ModelInfoList[i].color.w = 1.0f;


		m_ModelInfoList[i].positionX = (((float)rand() - (float)rand()) / RAND_MAX) * 20.0f;
		m_ModelInfoList[i].positionY = (((float)rand() - (float)rand()) / RAND_MAX) * 20.0f;
		m_ModelInfoList[i].positionZ = ((((float)rand() - (float)rand()) / RAND_MAX) * 10.0f) + 25.0f;

	}

	return true;

}

void ModelListClass::Shutdown()
{
	// Release the model information list.
	if (m_ModelInfoList)
	{
		delete[] m_ModelInfoList;
		m_ModelInfoList = 0;
	}

	return;
}

int ModelListClass::GetModelCount()
{
	return m_modelCount;
}

void ModelListClass::GetData(int index, float& positionX, float& positionY, float& positionZ, XMVECTOR& color)
{
	positionX = m_ModelInfoList[index].positionX;
	positionY = m_ModelInfoList[index].positionY;
	positionZ = m_ModelInfoList[index].positionZ;

	color = XMLoadFloat4(&m_ModelInfoList[index].color);

	return;
}