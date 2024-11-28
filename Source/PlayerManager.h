#pragma once

#include <vector>
#include "Player.h"
#include "Character.h"

class PlayerManager
{
private:
	PlayerManager() {};
	~PlayerManager() {};

public:
	//唯一のインスタンス取得	オブザーバーパターン
	static PlayerManager& Instance()
	{
		static PlayerManager instance;
		return instance;
	}

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//ステージ登録
	void Register(Player* player);

	//ステージ全削除
	void Clear();

	//レイキャスト
	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit);

	//ピース数取得
	int GetPlayerCount()const { return static_cast<int>(players.size()); }

	//ピース取得
	Player* GetPlayer(int index) { return players.at(index); }

private:
	// 配列
	std::vector<Player*> players;
};