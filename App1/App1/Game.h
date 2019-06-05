#pragma once

using namespace Microsoft::WRL;
using namespace Windows::UI::Core;
using namespace DirectX;

class CGame
{
public:
	ComPtr<ID3D11Device1> dev;              // the device interface
	ComPtr<ID3D11DeviceContext1> devcon;    // the device context interface
	ComPtr<IDXGISwapChain1> swapchain;
	ComPtr<ID3D11RenderTargetView> rendertarget;    // added to the CGame class
	ComPtr<ID3D11Buffer> vertexbuffer;
	ComPtr<ID3D11VertexShader> vertexshader;
	ComPtr<ID3D11PixelShader> pixelshader;
	ComPtr<ID3D11InputLayout> inputlayout;    // the input layout interface

	struct VERTEX
	{
		float X, Y, Z;    // vertex position
	};

	Array<byte>^ LoadShaderFile(std::string File);

	void Initialize();
	void Update();
	void Render();
	void SetColor(float color[4]);
	void InitGraphics();

	void InitPipeline();

private:
		float color[4];
};