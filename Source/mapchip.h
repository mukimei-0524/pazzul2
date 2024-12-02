#pragma once

#include "Character.h"
#include "Graphics/Graphics.h"

//クラスは全体のことではなく個のことを書く
//ゲープロでいうエネミー
class MapChip:public Character
{
public:
	MapChip() {};
	~MapChip()override {};

	//更新処理
	virtual void Update(float elapsedTime) = 0;

	//描画処理
	virtual void Render(ID3D11DeviceContext* dc, Shader* shader) = 0;

	void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }

};