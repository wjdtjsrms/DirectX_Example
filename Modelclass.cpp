#include "Modelclass.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D11Device* device){
	bool result;

	// ���� ���ۿ� �ε��� ���۸� �ʱ�ȭ�մϴ�.
	result=InitializeBuffers(device);
	if(!result){
		return false;
	}
	return true;
}

void ModelClass::Shutdown(){
	//private�� �ִ°Ÿ� �̷��� ȣ���ϳ�?
	// ���� ���ۿ� �ε��� ���۸� �����մϴ�.
	ShutdownBuffers();
	return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext){

	/* ���� ���ۿ� �ε��� ���۸� �׷��Ƚ� ���������ο� �־� ȭ�鿡 �׸� �غ� �մϴ�.*/
	RenderBuffers(deviceContext);

	return;
}

int ModelClass::GetIndexCount(){

	return m_indexCount;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device){
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc,indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData,indexData;
	HRESULT result;
	


	m_indexCount=3;

	m_vertexCount=3;

	vertices= new VertexType[m_vertexCount];
	if(!vertices){
		return false;
	}
	indices=new unsigned long[m_indexCount];
	if(!indices){
		return false;
	}
	
	vertices[0].position=&XMVectorSet(-1.0f, -1.0f, 0.0f,0.0f);
	vertices[0].color=&XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[1].position=&XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	vertices[1].color=&XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position=&XMVectorSet(1.0f, -1.0f, 0.0f,0.0f);
	vertices[2].color=&XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	indices[0]=0;
	indices[1]=1;
	indices[2]=2;

	// ���� ������ description�� �ۼ��մϴ�.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT; //gpu�� ������ �ڿ��� �а� ��� �Ѵٸ� �� �뵵�� �����Ѵ�.
	//ũ�⸦ ��Ȯ�ϰ� �Է��ؾ� �Ѵ�
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;


	// ���� ���۸� �����մϴ�.
	result=device->CreateBuffer(&vertexBufferDesc,&vertexData,&m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// �ε��� ������ description�� �ۼ��մϴ�.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// �ε��� �����͸� ����Ű�� ���� ���ҽ� ����ü�� �ۼ��մϴ�.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// �ε��� ���۸� �����մϴ�.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	delete[] vertices;
	vertices=0;

	delete[] indices;
	indices=0;

	return true;
}

// InitializeBuffers �Լ����� ������� ���� ���ۿ� �ε��� ���۸� �����ϴ� ���� �մϴ�.
void ModelClass::ShutdownBuffers()
{
	// �ε��� ���۸� �����մϴ�.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// ���� ���۸� �����մϴ�.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// ���� ������ ������ �������� �����մϴ�.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// input assembler�� ���� ���۸� Ȱ��ȭ�Ͽ� �׷��� �� �ְ� �մϴ�.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // input assembler�� �ε��� ���۸� Ȱ��ȭ�Ͽ� �׷��� �� �ְ� �մϴ�.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // ���� ���۷� �׸� �⺻���� �����մϴ�. ���⼭�� �ﰢ���Դϴ�.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}