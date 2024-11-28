#pragma once

#include <vector>
#include "mapchip.h"

class ChipManager
{
private:
	ChipManager() {};
	~ChipManager() {};

public:
	//唯一のインスタンス取得
	static ChipManager& Instance()
	{
		static ChipManager instance;
		return instance;
	}

	//更新処理
	void Update(float elapsedTIme);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

private:
	std::vector<MapChip*>chips;


};