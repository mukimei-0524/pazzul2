#pragma once

#include <memory>
#include <wrl.h>
#include "Graphics/Shader.h"

class LambertShader : public Shader
{
public:
	LambertShader(ID3D11Device* device);
	~LambertShader() override {}

	void Begin(ID3D11DeviceContext* dc, const RenderContext& rc) override;
	void Draw(ID3D11DeviceContext* dc, const Model* model) override;
	void End(ID3D11DeviceContext* dc) override;

	//�F�ݒ�
	void SetColor(const DirectX::XMFLOAT4& color);

private:
	static const int MaxBones = 256;

	float alpha = 0.5f;

	struct CbScene
	{
		DirectX::XMFLOAT4X4	viewProjection;
		DirectX::XMFLOAT4	lightDirection;
	};

	struct CbMesh
	{
		DirectX::XMFLOAT4X4	boneTransforms[MaxBones];
	};

	struct CbSubset
	{
		DirectX::XMFLOAT4	materialColor;
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer>			sceneConstantBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			meshConstantBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			subsetConstantBuffer;

	Microsoft::WRL::ComPtr<ID3D11VertexShader>		vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>		pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>		inputLayout;

	Microsoft::WRL::ComPtr<ID3D11BlendState>		blendState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>	rasterizerState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>	depthStencilState;

	Microsoft::WRL::ComPtr<ID3D11SamplerState>		samplerState;
};
