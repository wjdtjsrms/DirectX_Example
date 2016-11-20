#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include"D3dclass.h"
#include "Cameraclass.h"
#include "Modelclass.h"
#include "Colorshaderclass.h"


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


class Graphicsclass{

public:
	Graphicsclass();
	Graphicsclass(const Graphicsclass&);
	~Graphicsclass();
	
	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();


private:
	bool Render();
private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;

};

#endif