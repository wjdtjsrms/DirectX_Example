#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_

#include <d3d11.h>
#include <xnamath.h>


class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	XMVECTOR GetPosition();
	XMVECTOR GetRotation();
	

	void Render();
	XMMATRIX GetViewMatrix();

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	XMVECTOR* m_Vpostion;
	XMMATRIX* m_viewMatrix;
};

#endif