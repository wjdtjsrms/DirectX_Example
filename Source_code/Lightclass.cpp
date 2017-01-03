#include "../Header_file/Lightclass.h"

LightClass::LightClass()
{
}


LightClass::LightClass(const LightClass& other)
{
}


LightClass::~LightClass()
{
}

void LightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void LightClass::SetDirection(float x, float y, float z)
{
	m_direction = XMFLOAT3(x, y, z);
	return;
}

void LightClass::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor= XMFLOAT4(red, green, blue, alpha);
	return;
}

void LightClass::GetDiffuseColor(XMVECTOR& diffuseColor )
{
	diffuseColor = XMLoadFloat4(&m_diffuseColor);
	return;
}

void LightClass::GetDirection(XMVECTOR& direction)
{
	direction = XMLoadFloat3(&m_direction);
	return;
}

void LightClass::GetAmbientColor(XMVECTOR& ambeintColor)
{
	ambeintColor = XMLoadFloat4(&m_ambientColor);
	return;
}