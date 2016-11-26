#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_

#include <D3D11.h>
#include <xnamath.h>

class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();

	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);

	void GetDiffuseColor(XMVECTOR&);
	void GetDirection(XMVECTOR&);

private:
	XMFLOAT4 m_diffuseColor;
	XMFLOAT3 m_direction;
};



#endif