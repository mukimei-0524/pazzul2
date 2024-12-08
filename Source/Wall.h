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

private:
	//モデル入れる
	Model* model = nullptr;
};