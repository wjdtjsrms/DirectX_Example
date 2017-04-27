#include "../Header_file/Frustumclass.h"


FrustumClass::FrustumClass(){

	m_frustum = 0;
}

FrustumClass::FrustumClass(const FrustumClass& other){


}

FrustumClass::~FrustumClass(){


}

void FrustumClass::ConstructFrustum(float screenDepth, XMMATRIX& projectionMatrix, XMMATRIX& viewMatrix){

	float zMinmum, r;
	XMMATRIX matrix;
	

	zMinmum = -projectionMatrix._43 / projectionMatrix._33;
	r = screenDepth / (screenDepth - zMinmum);
	projectionMatrix._33 = r;
	projectionMatrix._43 = -r*zMinmum;

	matrix=XMMatrixMultiply(viewMatrix, projectionMatrix);

	// Calculate near plane of frustum.
	m_planes[0].x = matrix._14 + matrix._13;
	m_planes[0].y = matrix._24 + matrix._23;
	m_planes[0].z = matrix._34 + matrix._33;
	m_planes[0].w = matrix._44 + matrix._43;
	XMStoreFloat4(&m_planes[0], XMPlaneNormalize(XMLoadFloat4(&m_planes[0])));


	// Calculate far plane of frustum.
	m_planes[1].x = matrix._14 - matrix._13;
	m_planes[1].y = matrix._24 - matrix._23;
	m_planes[1].z = matrix._34 - matrix._33;
	m_planes[1].w = matrix._44 - matrix._43;
	XMStoreFloat4(&m_planes[1], XMPlaneNormalize(XMLoadFloat4(&m_planes[1])));

	// Calculate left plane of frustum.
	m_planes[2].x = matrix._14 + matrix._11;
	m_planes[2].y = matrix._24 + matrix._21;
	m_planes[2].z = matrix._34 + matrix._31;
	m_planes[2].w = matrix._44 + matrix._41;
	XMStoreFloat4(&m_planes[2], XMPlaneNormalize(XMLoadFloat4(&m_planes[2])));

	// Calculate right plane of frustum.
	m_planes[3].x = matrix._14 - matrix._11;
	m_planes[3].y = matrix._24 - matrix._21;
	m_planes[3].z = matrix._34 - matrix._31;
	m_planes[3].w = matrix._44 - matrix._41;
	XMStoreFloat4(&m_planes[3], XMPlaneNormalize(XMLoadFloat4(&m_planes[3])));

	// Calculate top plane of frustum.
	m_planes[4].x = matrix._14 - matrix._12;
	m_planes[4].y = matrix._24 - matrix._22;
	m_planes[4].z = matrix._34 - matrix._32;
	m_planes[4].w = matrix._44 - matrix._42;
	XMStoreFloat4(&m_planes[4], XMPlaneNormalize(XMLoadFloat4(&m_planes[4])));

	// Calculate bottom plane of frustum.
	m_planes[5].x = matrix._14 + matrix._12;
	m_planes[5].y = matrix._24 + matrix._22;
	m_planes[5].z = matrix._34 + matrix._32;
	m_planes[5].w = matrix._44 + matrix._42;
	XMStoreFloat4(&m_planes[5], XMPlaneNormalize(XMLoadFloat4(&m_planes[5])));


	return;


}

void FrustumClass::makeVector(XMVECTOR& vector, float Value_x, float Value_y, float Value_z, float Value_w){

	XMFLOAT4 local_float;
	local_float.x = Value_x;
	local_float.y = Value_x;
	local_float.z = Value_x;
	local_float.w = Value_x;

	XMStoreFloat4(&local_float, vector);

}


bool FrustumClass::CheckPoint(float x, float y, float z){

	int i;
	XMVECTOR vector = XMVectorSet(x, y, z, 1);
	XMFLOAT4 save_plane;

	for (i = 0; i < 6; i++){
		XMStoreFloat4(&save_plane, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), vector));
		if (save_plane.x<-15.0f){
			return false;
		}
	}

	return true;
}

bool FrustumClass::CheckCube(float xCenter, float yCenter, float zCenter, float radius){

	int i;
	XMVECTOR vector = XMVectorSet(0, 0, 0, 1);
	XMFLOAT4 save_plane;


	for (i = 0; i < 6; i++){
		makeVector(vector, (xCenter - radius), (yCenter - radius), (zCenter - radius),1.0f);
		XMStoreFloat4(&save_plane, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), vector));

		if (save_plane.x>= 0.0f)
		{
			continue;
		}

		makeVector(vector, (xCenter + radius), (yCenter - radius), (zCenter - radius), 1.0f);
		XMStoreFloat4(&save_plane, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), vector));

		if (save_plane.x >= 0.0f)
		{
			continue;
		}

		makeVector(vector, (xCenter - radius), (yCenter + radius), (zCenter - radius), 1.0f);
		XMStoreFloat4(&save_plane, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), vector));

		if (save_plane.x >= 0.0f)
		{
			continue;
		}

		makeVector(vector, (xCenter + radius), (yCenter + radius), (zCenter - radius), 1.0f);
		XMStoreFloat4(&save_plane, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), vector));

		if (save_plane.x >= 0.0f)
		{
			continue;
		}

		makeVector(vector, (xCenter - radius), (yCenter - radius), (zCenter + radius), 1.0f);
		XMStoreFloat4(&save_plane, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), vector));

		if (save_plane.x >= 0.0f)
		{
			continue;
		}

		makeVector(vector, (xCenter + radius), (yCenter - radius), (zCenter + radius), 1.0f);
		XMStoreFloat4(&save_plane, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), vector));

		if (save_plane.x >= 0.0f)
		{
			continue;
		}

		makeVector(vector, (xCenter - radius), (yCenter + radius), (zCenter + radius), 1.0f);
		XMStoreFloat4(&save_plane, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), vector));

		if (save_plane.x >= 0.0f)
		{
			continue;
		}

		makeVector(vector, (xCenter + radius), (yCenter + radius), (zCenter + radius), 1.0f);
		XMStoreFloat4(&save_plane, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), vector));

		if (save_plane.x >= 0.0f)
		{
			continue;
		}

		return false;


	}

	return true;
}

bool FrustumClass::CheckSphere(float xCenter, float yCenter, float zCenter,float radius){

	int i;
	XMVECTOR vector = XMVectorSet(xCenter, yCenter, zCenter, 1);
	XMFLOAT4 save_plane;

	for (i = 0; i < 6; i++){
		XMStoreFloat4(&save_plane, XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), vector));
		if (save_plane.x<-radius){
			return false;
		}
	}

	return true;
}