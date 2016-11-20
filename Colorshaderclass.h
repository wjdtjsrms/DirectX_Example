#ifndef _COLORSHADERCLASS_H_
#define _COLORSHADERCLASS_H_

#include <d3d11.h>
#include <xnamath.h>
#include <D3DX11async.h>
#include <fstream>

using namespace std;

class ColorShaderClass
{
private:
	struct MatrixBufferType
{
	XMMATRIX worldMatrix; //xmflaot?
	XMMATRIX viewMatrix;
	XMMATRIX projectioMatrix;
	
};

public:
	ColorShaderClass();
	ColorShaderClass(const ColorShaderClass&);
	~ColorShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX& ,XMMATRIX&, XMMATRIX&); //딱 보니까 월드 투영, 뷰 투영 직교 투영 각이다. 응 인정

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX&, XMMATRIX&, XMMATRIX&);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
};



#endif