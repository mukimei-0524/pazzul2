#pragma once

#include "Character.h"
#include "Graphics/Sprite.h"

class MapChip:public Character
{
public:
	enum class CHIPS	//マップチップの種類
	{
		WITH,		//０：印あり(かけらが埋まっている)
		WHITHOUT	//１：印なし(かけらが埋まっていない)
	};

public:
	MapChip();
	~MapChip() override {};

	void Update(float elapsedTime);

	void Render();

private:
	DirectX::XMFLOAT2 position{ 0,0 };

	Sprite* chips = nullptr;
};