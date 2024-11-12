#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Character.h"
#include "Effect.h"

//プレイヤー
class Player :public Character
{
public:
	Player();
	~Player() override;

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//デバッグ用GUI描画
	void DrawDebugGUI();

	//デバッグプリミティブ描画
	void DrawDebugPrimitive();

	//ジャンプ入力処理
	void InputJump();

protected:
	//着地したときに呼ばれる
	void OnLanding() override;

private:
	Model* model = nullptr;
	Effect* hitEffect = nullptr;
	float turnSpeed = DirectX::XMConvertToRadians(720);
	float moveSpeed = 5.0f;

	float jumpSpeed = 20.0f;
	
	int jumpCount = 0;
	int jumpLimit = 2;

	//スティック入力値から移動ベクトルを取得
	DirectX::XMFLOAT3 GetMoveVec() const;

	//入力処理
	void InputMove(float elapsedTime);
};

//elapsedTime:経過時間