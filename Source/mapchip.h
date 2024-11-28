#pragma once

#include "Character.h"
#include "Graphics/Graphics.h"

//クラスは全体のことではなく個のことを書く
class MapChip:public Character
{
public:
	enum class CHIPS	//マップチップの種類
	{
		WITH,		//０：印あり(かけらが埋まっている)
		WHITHOUT	//１：印なし(かけらが埋まっていない)
	};

public:
	MapChip() {};
	~MapChip() override {};

	//更新処理
	virtual void Update(float elapsedTime) = 0;

	//描画処理
	virtual void Render(ID3D11DeviceContext* dc, Shader* shader) = 0;

private:
	Model* chips = nullptr;
};