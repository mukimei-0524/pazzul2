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
	void Update(float elapsedTime);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//チップ登録
	void Register(MapChip* chips);

	void Clear();

private:
	//配列
	std::vector<MapChip*>chips;
};