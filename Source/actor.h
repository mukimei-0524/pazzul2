#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include <string>

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

	// �J�E���g��ۑ�����ϐ���ǉ�
	int clickCount = 0;

	// �V�����֐���錾
	void HandleClick(int mouseX, int mouseY);

	// �f�o�b�O�p�̃N���b�N���W
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

	//�ړ����͏���
	bool InputMove(float elapsedTime);

	Model* model = nullptr;

	float moveSpeed = 50.0f;
	float turnSpeed = DirectX::XMConvertToRadians(720);

	State state = State::Jump;

	// �f�o�b�O������
	std::string debugInfo;

private:
	void TransitionIdleState();

	void UpdateIdleState(float elapsedTime);
	
	void TransitionMineState();

	void UpdateMineState(float elapsedTime);

	void TransitionJumpState();

	void UpdateJumpState(float elapsedTime);
};