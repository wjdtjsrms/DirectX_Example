#include "Graphicsclass.h"

Graphicsclass::Graphicsclass(){
	m_D3D=0;
	m_Camera = 0;
	m_Model = 0;
	m_ColorShader = 0;
}
Graphicsclass::Graphicsclass(const Graphicsclass& other){
}
Graphicsclass::~Graphicsclass(){
}

bool Graphicsclass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	
	bool result;

	// Create the Direct3D object.
	m_D3D=new D3DClass;

	if(!m_D3D)
	{
		return false;
	}

	result=m_D3D->Initialize(screenWidth,screenHeight,VSYNC_ENABLED,hwnd,FULL_SCREEN,SCREEN_DEPTH,SCREEN_NEAR);
	if(!result)
	{
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Create the model object.
	m_Model = new ModelClass;
	if(!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if(!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}


	return true;
}

void Graphicsclass::Shutdown()
{
	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the color shader object.
	if(m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}


	return;
}


bool Graphicsclass::Frame()
{
	bool result;


	// 그래픽 렌더링을 수행합니다.

	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool Graphicsclass::Render()
{
	XMMATRIX worldMatrix(1.0f, 0.0f, 0.0f, 0.0f,
						 0.0f, 1.0f, 0.0f, 0.0f,
						 0.0f, 0.0f, 1.0f, 0.0f,
						 0.0f, 0.0f, 0.0f, 1.0f);

	XMMATRIX projectionMatrix(1.80947561f, 0.0f, 0.0f, 0.0f,
							  0.0f, 2.41421342f, 0.0f, 0.0f,
							  0.0f, 0.0f, 1.00010002f, 0.0f,
							  0.0f, 0.0f, -0.100010000f, 0.0f);
	XMMATRIX viewMatrix;
	bool result;

	 //씬 그리기를 시작하기 위해 버퍼의 내용을 지웁니다.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);


	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	//value copy로 바꿈
	//worldMatrix = m_D3D->GetWorldMatrix(); 
	//projectionMatrix = m_D3D->GetProjectionMatrix();
	viewMatrix=m_Camera->GetViewMatrix();
	



	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the color shader.
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if(!result)
	{
		return false;
	}

	// 버퍼에 그려진 씬을 화면에 표시합니다.
	m_D3D->EndScene();


	return true;
}