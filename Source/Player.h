#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Character.h"
#include "Effect.h"
#include "Collision.h"
#include "PlayerManager.h"

//playerをピースとする
//プレイヤー
class Player :public Character
{
public:
	Player(const char* filename);
	~Player() override;

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//デバッグ用GUI描画
	void DrawDebugGUI();

	// レイキャスト
	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit);

	// インスタント取得
	//static Player& Instance();

private:
	Model* model = nullptr;

	//プレイヤーのインデックス取得
	//PlayerManager& playerManager = PlayerManager::Instance();
	//int playerCount = playerManager.GetPlayerCount();
	//Player* player = playerManager.GetPlayer(i);

	//スティック入力値から移動ベクトルを取得
	DirectX::XMFLOAT3 GetMoveVec() const;
};