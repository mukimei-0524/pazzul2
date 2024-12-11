#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include <string>

#include "Character.h"
//プレイヤーの動き、アニメーション等

class Actor :public Character
{
public:
	Actor();
	~Actor() override;

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	// カウントを保存する変数を追加
	int clickCount = 0;

	// 新しい関数を宣言
	void HandleClick(int mouseX, int mouseY);

	// デバッグ用のクリック座標
	DirectX::XMFLOAT3 debugClickPosition = { 0.0f, 0.0f, 0.0f };


private:	
	enum Animation
	{
		MIne,
		Jump
	};


	enum class State
	{
		Idle,
		Mine,
		Jump
	};

	DirectX::XMFLOAT3 GetMoveVec() const;

	//移動入力処理
	bool InputMove(float elapsedTime);

	Model* model = nullptr;

	float moveSpeed = 50.0f;
	float turnSpeed = DirectX::XMConvertToRadians(720);

	State state = State::Jump;

	// デバッグ文字列
	std::string debugInfo;

private:
	void TransitionIdleState();

	void UpdateIdleState(float elapsedTime);
	
	void TransitionMineState();

	void UpdateMineState(float elapsedTime);

	void TransitionJumpState();

	void UpdateJumpState(float elapsedTime);
};