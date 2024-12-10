#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"

#include "Character.h"
//�v���C���[�̓����A�A�j���[�V������

class Actor :public Character
{
public:
	Actor();
	~Actor() override;

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
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

	//�ړ����͏���
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