#pragma once

#include "Graphics/Model.h"

#include "mapchip.h"
#include "Collision.h"

//ゲープロでいうエネミースライム
class Chip :public MapChip
{
public:
	Chip();
	~Chip()override;

	//更新処理
	void Update(float elapsedTime)override;

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader)override;

	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit);

private:
	//モデル入れる
	Model* chips = nullptr;
};