////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "../Header_file/graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Bitmap = 0;
	m_ModelList = 0;
	m_Frustum = 0;
	m_Text = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	XMMATRIX baseViewMatrix;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, 30.0f);

	
	// Create the model object.
	m_Model = new ModelClass;
	if(!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(),"Resource/test.obj","Resource/model.txt",L"Resource/uv_snap.dds"); //change file
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Bitmap = new BitmapClass;
	if (!m_Bitmap){
		return false;
	}
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"Resource/uv_snap.dds", 256, 256);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Bitmap object.", L"Error", MB_OK);
		return false;
	}





	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	m_TextureShader = new Textureshaderclass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-1.0f, 0.0f, 0.0f);
	m_Light->setSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	
	// Create the modellist object.
	m_ModelList = new ModelListClass;
	if (!m_ModelList){
		return false;
	}

	// Initialize the modellist object.
	result = m_ModelList->Initialize(15);

	if (!result){
		MessageBox(hwnd, L"Could not initialize the model list object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the Frustum object.
	m_Frustum = new FrustumClass;
	if (!m_Frustum){
		return false;
	}

	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	if (m_ModelList)
	{
		m_ModelList->Shutdown();
		delete m_ModelList;
		m_ModelList = 0;
	}

	if (m_Bitmap){
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
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

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(int mouseX, int mouseY, float player_X, float player_Y,int fps)
{
	bool result;
	float rotationX;
	float rotationY;

	rotationX = (float)XM_PI * (mouseX*0.0008f);

	
	rotationY = (float)XM_PI * (mouseY*0.0008f);
	

	// Render the graphics scene.
	result = Render(rotationX, rotationY,player_X,player_Y);
	if(!result)
	{
		return false;
	}
	result = m_Text->setFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}



	return true;
}


bool GraphicsClass::Render(float rotationX, float rotationY, float player_X, float player_Y)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	XMVECTOR Direction, DiffuseColor, AmbeintColor, SpecularColor, CameraPostion;
	XMMATRIX Rotation;
	XMVECTOR Color;
	
	float SpecularPower;
	float positionX, positionY, positionZ, radius;
	int modelCount,index,renderCount;
	bool renderModel,result;

	

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	viewMatrix = viewMatrix*XMMatrixRotationY(-rotationX)*XMMatrixRotationX(-rotationY);
	m_Frustum->ConstructFrustum(SCREEN_DEPTH, projectionMatrix, viewMatrix);


	

	

	//·»´õ ÇÒ ¸ðµ¨ÀÇ °¹¼ö °¡Á®¿À±â
	modelCount = m_ModelList->GetModelCount();

	renderCount = 0;

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	

	for (index = 0; index < modelCount; index++){
		m_ModelList->GetData(index, positionX, positionY, positionZ, Color);

		radius = 25.0f;

		renderModel = m_Frustum->CheckSphere(positionX, positionY, positionZ,radius);
		if (renderModel)
		{
			// Move the model to the location it should be rendered at.
			worldMatrix = worldMatrix*XMMatrixTranslation(positionX, positionY, positionZ);

			// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			m_Model->Render(m_D3D->GetDeviceContext());

			// Get the direction, diffuse color
			m_Light->GetDirection(Direction);
			m_Light->GetDiffuseColor(DiffuseColor);
			m_Light->GetAmbientColor(AmbeintColor);
			m_Light->GetSpecularColor(SpecularColor);
			m_Light->GetSpecularPower(SpecularPower);

			CameraPostion = XMLoadFloat3(&m_Camera->GetPosition());

		


			result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 10, 10);
			if (!result){
				return false;
			}


			m_Model->Render(m_D3D->GetDeviceContext());

			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), Direction, DiffuseColor, AmbeintColor, CameraPostion, SpecularColor, SpecularPower);
			if (!result)
			{
				return false;
			}

			m_D3D->GetWorldMatrix(worldMatrix);

			renderCount++;
			// Set the number of models that was actually rendered this frame.
		

		}

	

	}

	printf("%d", renderCount);
	result = m_Text->SetRenderCount(renderCount, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text string of the render count.
	m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();
	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();



	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}