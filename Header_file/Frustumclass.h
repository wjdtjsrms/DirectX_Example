#ifndef _FRUSTMCLASS_H_
#define _FRUSTMCLASS_H_

#include <d3d11.h>
#include <xnamath.h>
#include <xnacollision.h>


class FrustumClass{
public :
	FrustumClass();
	FrustumClass(const FrustumClass&);
	~FrustumClass();

	void ConstructFrustum(float, XMMATRIX&, XMMATRIX&);

	bool CheckPoint(float, float, float);
	bool CheckCube(float,float,float,float);
	bool CheckSphere(float,float,float,float);
	bool CheckRectangle(float,float,float,float,float,float);
	void makeVector(XMVECTOR&,float, float, float, float);

private:

	//d3d->float->xna
	XMFLOAT4 m_planes[6];
	FrustumClass* m_frustum;
	
	
};

#endif