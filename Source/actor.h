#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"

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


private:	
	enum Animation
	{
		Jump
	};


	enum class State
	{
		Idle,
		Jump
	};

	DirectX::XMFLOAT3 GetMoveVec() const;

	//移動入力処理
	bool InputMove(float elapsedTime);

	Model* model = nullptr;

	float moveSpeed = 50.0f;
	float turnSpeed = DirectX::XMConvertToRadians(720);

	State state = State::Jump;

private:
	void TransitionIdleState();

	void UpdateIdleState(float elapsedTime);

	void TransitionJumpState();

	void UpdateJumpState(float elapsedTime);
};