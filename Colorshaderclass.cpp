#include "Colorshaderclass.h"

ColorShaderClass::ColorShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
}


ColorShaderClass::ColorShaderClass(const ColorShaderClass& other)
{
}


ColorShaderClass::~ColorShaderClass()
{
}

bool ColorShaderClass::Initialize(ID3D11Device* device,HWND	hwnd){
	bool result;

	result=InitializeShader(device,hwnd,L"Color.vs", L"Color.ps");
	if(!result){
		return false;
	}

	return true;

}

void ColorShaderClass::Shutdown()
{
	// ���� ���̴��� �Ƚ� ���̴� �� �׿� ���õ� �͵��� ��ȯ�մϴ�.
	ShutdownShader();

	return;
}

bool ColorShaderClass::Render(ID3D11DeviceContext* deviceContext,int indexCount,  XMMATRIX &worldMatrix,XMMATRIX &viewMatrix,XMMATRIX &projectionMatrix){

	bool result;

	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);

	if(!result)
	{
		return false;
	}

	RenderShader(deviceContext, indexCount);
	
	return true;

}

bool ColorShaderClass::InitializeShader(ID3D11Device* device,HWND hwnd,WCHAR* vsFilename,WCHAR* psFilename){

	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	//������ �ʱ�ȭ
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	// ���� ���̴��� �������մϴ�.
	result = D3DX11CompileFromFile(vsFilename, NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL,&vertexShaderBuffer, &errorMessage, NULL);

	if(FAILED(result))
	{
		// ���̴��� �����Ͽ� �����ϸ� ���� �޼����� ����մϴ�.
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		// ���� �޼����� ���ٸ� ���̴� ������ ã�� ���� ���Դϴ�.
		else
		{
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	// �ȼ� ���̴��� �������մϴ�.
	result = D3DX11CompileFromFile(psFilename, NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
									&pixelShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		// ���̴� �������� �����ϸ� ���� �޼����� ����մϴ�.
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		// ���� �޼����� ���ٸ� �ܼ��� ���̴� ������ ã�� ���� ���Դϴ�.
		else
		{
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	 // ���۷κ��� ���� ���̴��� �����մϴ�.
	result =device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),vertexShaderBuffer->GetBufferSize(),NULL,&m_vertexShader);

	if(FAILED(result))
	{
		return false;
	}

	// ���۷κ��� �ȼ� ���̴��� �����մϴ�.
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if(FAILED(result))
	{
		return false;
	}

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	numElements=sizeof(polygonLayout)/sizeof(polygonLayout[0]);
	result=device->CreateInputLayout(polygonLayout,numElements,vertexShaderBuffer->GetBufferPointer(),vertexShaderBuffer->GetBufferSize(),&m_layout);

	if(FAILED(result))
	{
		return false;
	}

	vertexShaderBuffer->Release();
	vertexShaderBuffer=0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer=0;

	// ���� ���̴��� �ִ� ��� ��� ������ description�� �ۼ��մϴ�.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// ��� ���� �����͸� ����� �� Ŭ�������� ���� ���̴� ��� ���ۿ� ������ �� �ְ� �մϴ�.
	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

void ColorShaderClass::ShutdownShader(){

	// ��� ���۸� �����մϴ�.
	if(m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	// ���̾ƿ��� �����մϴ�.
	if(m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	// �ȼ� ���̴��� �����մϴ�.
	if(m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	// ���� ���̴��� �����մϴ�.
	if(m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}

	return;
}

void ColorShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


	// ���� �޼����� ��� �ִ� ���ڿ� ������ �����͸� �����ɴϴ�.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// �޼����� ���̸� �����ɴϴ�.
	bufferSize = errorMessage->GetBufferSize();

	// ������ ���� �ȿ� �޼����� ����մϴ�.
	fout.open("shader-error.txt");

	// ���� �޼����� ���ϴ�.
	for(i=0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// ������ �ݽ��ϴ�.
	fout.close();

	// ���� �޼����� ��ȯ�մϴ�.
	errorMessage->Release();
	errorMessage = 0;

	// ������ ������ ������ �˾� �޼����� �˷��ݴϴ�.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}

bool ColorShaderClass::SetShaderParameters(ID3D11DeviceContext* deviceContext,XMMATRIX& worldMatrix,XMMATRIX& viewMatrix,XMMATRIX& projectionMatrix){
	
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;
	
	// ����� transpose(��ġ)�Ͽ� ���̴����� ����� �� �ְ� �մϴ�. 
	worldMatrix=XMMatrixTranspose(worldMatrix);
	viewMatrix=XMMatrixTranspose(viewMatrix);
	projectionMatrix=XMMatrixTranspose(projectionMatrix);

	result=deviceContext->Map(m_matrixBuffer,0,D3D11_MAP_WRITE_DISCARD,0,&mappedResource);

	if(FAILED(result))
	{
		return false;
	}

	// ��� ������ �����Ϳ� ���� �����͸� �����ɴϴ�.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// ��� ���ۿ� ����� �����մϴ�.
	dataPtr->worldMatrix=worldMatrix;
	dataPtr->projectioMatrix=projectionMatrix;
	dataPtr->viewMatrix=viewMatrix;

	// ��� ������ ����� Ǳ�ϴ�.
	deviceContext->Unmap(m_matrixBuffer,0);

	bufferNumber=0;

	deviceContext->VSSetConstantBuffers(bufferNumber,1,&m_matrixBuffer);


	return true;
}

void ColorShaderClass::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	// ���� �Է� ���̾ƿ��� �����մϴ�.
	deviceContext->IASetInputLayout(m_layout);

	// �ﰢ���� �׸� ���� ���̴��� �ȼ� ���̴��� �����մϴ�.
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	// �ﰢ���� �׸��ϴ�.
	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}