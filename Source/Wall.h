#pragma once
#include "mapchip.h"

class Wall :public MapChip
{
public:
	Wall();
	~Wall()override;

	//更新処理
	void Update(float elapsedTime)override;

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader)override;

	//行列更新処理
	void UpdateTransform();

protected:
	DirectX::XMFLOAT3		position = { 0,0,0 };
	DirectX::XMFLOAT3		angle = { 0,0,0 };
	DirectX::XMFLOAT3		scale = { 1,1,1 };
	DirectX::XMFLOAT4X4		transform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

private:
	//モデル入れる
	Model* model = nullptr;
};