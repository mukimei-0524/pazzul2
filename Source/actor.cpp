#include "Input/Input.h"
#include "Graphics/Graphics.h"

#include "actor.h"
#include "camera.h"

Actor::Actor()
{
	model = new Model("Data/Model/team/MDL/Character_jump.mdl");

	TransitionIdleState();
}

Actor::~Actor()
{
	delete model;
}

void Actor::Update(float elapsedTime)
{
	//�ړ����͏���
	InputMove(elapsedTime);

	//�i�s�x�N�g���擾
	DirectX::XMFLOAT3 moveVec = GetMoveVec();

	//���f���A�j���[�V�����X�V����
	model->UpdateAnimation(elapsedTime);

	//�I�u�W�F�N�g�s��X�V
	UpdateTransform();

	//���f���s��X�V
	model->UpdateTransform(transform);


	//���s���[�V�����ƃW�����v���[�V�������ꏏ�̃��f�������炤�H
	//��U�X�y�[�X�L�[�Ō@�郂�[�V����(�f�o�b�O�p�B��ő��k)
	//�G���^�[�����Ń����V���b�g�A�j���[�V�����Đ�(�̂��Ƀ}�E�X�őI�������}�X�ɐi�߂鏈���ɕύX)
	GamePad& gamePad = Input::Instance().GetGamePad();
	if (gamePad.GetButtonDown() & GamePad::BTN_BACK)
	{
		model->PlayAnimation(Jump, true);
	}

	switch (state)
	{
	case State::Idle:
		UpdateIdleState(elapsedTime);
		break;
	
	case State::Jump:
		UpdateJumpState(elapsedTime);
		break;
	}
}

void Actor::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);
}

DirectX::XMFLOAT3 Actor::GetMoveVec() const
{
	//���͏����擾
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();

	//�J���������ƃX�e�B�b�N�̓��͒l�ɂ���Đi�s�������v�Z����
	Camera& camera = Camera::Instance();
	const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
	const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

	DirectX::XMFLOAT3 vec;
	//�J�����E�����x�N�g����XZ�P�ʃx�N�g���ɕϊ�
	float cameraRightX = cameraRight.x;
	float cameraRightZ = cameraRight.z;
	float cameraRightLength = sqrtf(cameraRightX * cameraRightX + cameraRightZ * cameraRightZ);
	if (cameraRightLength > 0.0f)
	{
		//�P�ʃx�N�g����
		cameraRightX /= cameraRightLength;
		cameraRightZ /= cameraRightLength;
	}

	//�J�����O�����x�N�g����XZ�P�ʃx�N�g���ɕϊ�
	float cameraFrontX = cameraFront.x;
	float cameraFrontZ = cameraFront.z;
	float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX + cameraFrontZ * cameraFrontZ);
	if (cameraFrontLength > 0.0f)
	{
		//�P�ʃx�N�g����
		cameraFrontX /= cameraFrontLength;
		cameraFrontZ /= cameraFrontLength;
	}

	//�X�e�B�b�N�̐������͒l���J�����E�����ɔ��f���A
	//�X�e�B�b�N�̐������͒l���J�����O�����ɔ��f���A
	//�i�s�x�N�g�����v�Z����
	vec.x = cameraRightX * ax + cameraFrontX * ay;
	vec.z = cameraRightZ * ax + cameraFrontZ * ay;
	//Y�������ɂ͈ړ����Ȃ�
	vec.y = 0.0f;

	return vec;
}

bool Actor::InputMove(float elapsedTime)
{
	//�i�s�x�N�g���擾
	DirectX::XMFLOAT3 moveVec = GetMoveVec();

	//�ړ�����
	Move(elapsedTime,moveVec.x, moveVec.z, moveSpeed);

	//���񏈗�
	Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);

	return moveVec.x != 0.0f || moveVec.y != 0.0f || moveVec.z != 0.0f;
}

void Actor::TransitionIdleState()
{
	state = State::Idle;
}

void Actor::UpdateIdleState(float elapsedTime)
{
	if (InputMove(elapsedTime))
	{
		TransitionJumpState();
	}
}

void Actor::TransitionJumpState()
{
	state = State::Jump;

	model->PlayAnimation(Jump, true);
}

void Actor::UpdateJumpState(float elapsedTime)
{
	if (!InputMove(elapsedTime))
	{
		TransitionIdleState();
	}
}
//�z����
// �`�b�v�N���X�p�������N���X���Henum�Ǘ��H
//y�����]������
//����
//8.5x8.5
//chip class�Ŏ擾�ς݂��ǂ����̃t���O