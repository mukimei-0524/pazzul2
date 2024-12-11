#include "Input/Input.h"
#include "Graphics/Graphics.h"
#include <DirectXMath.h>
#include <sstream>
#include "Camera.h"

#include "actor.h"
#include "camera.h"

Actor::Actor()
{
	model = new Model("Data/Model/team/MDL/character.mdl");

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
		TransitionJumpState();
	}
	
	//�@��
	Mouse& mouse = Input::Instance().GetMouse();
	// �}�E�X�N���b�N�`�F�b�N
	if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
	{
		HandleClick(mouse.GetPositionX(), mouse.GetPositionY());
		TransitionMineState();
	}

	switch (state)
	{
	case State::Idle:
		UpdateIdleState(elapsedTime);
		break;
	
	case State::Mine:
		UpdateMineState(elapsedTime);
		break;
	
	case State::Jump:
		UpdateJumpState(elapsedTime);
		break;
	}
}

void Actor::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);

	// �f�o�b�O�p�̃e�L�X�g�`��
	//Graphics::Instance().DrawText(debugInfo, 10, 10, { 1.0f, 1.0f, 1.0f }); // ���W(10, 10)�ɔ��F�ŕ`��
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

// �@��
void Actor::TransitionMineState()
{
	state = State::Mine;

	model->PlayAnimation(MIne, false);
}

void Actor::UpdateMineState(float elapsedTime)
{
	if (!InputMove(elapsedTime))
	{
		TransitionIdleState();
	}
}

// �W�����v
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

void Actor::HandleClick(int mouseX, int mouseY)
{
	// �X�N���[�����W�𐳋K���f�o�C�X���W�ɕϊ� (-1.0 �` 1.0 �͈̔͂Ƀ}�b�s���O)
	float ndcX = (2.0f * mouseX) / Graphics::Instance().GetScreenWidth() - 1.0f;
	float ndcY = 1.0f - (2.0f * mouseY) / Graphics::Instance().GetScreenHeight();

	// �J��������r���[�s��ƃv���W�F�N�V�����s����擾
	DirectX::XMFLOAT4X4 viewMatrixFloat4x4 = Camera::Instance().GetView();
	DirectX::XMFLOAT4X4 projectionMatrixFloat4x4 = Camera::Instance().GetProjection();

	// XMMATRIX �ɕϊ�
	DirectX::XMMATRIX viewMatrix = DirectX::XMLoadFloat4x4(&viewMatrixFloat4x4);
	DirectX::XMMATRIX projectionMatrix = DirectX::XMLoadFloat4x4(&projectionMatrixFloat4x4);

	// �t���e�s����v�Z
	DirectX::XMMATRIX invViewProj = DirectX::XMMatrixInverse(nullptr, viewMatrix * projectionMatrix);

	// ���K���f�o�C�X���W�����[���h���W�ɕϊ�
	DirectX::XMVECTOR rayOrigin = DirectX::XMVector3TransformCoord(
		DirectX::XMVectorSet(ndcX, ndcY, 0.0f, 1.0f), invViewProj
	);

	DirectX::XMVECTOR rayDir = DirectX::XMVector3TransformNormal(
		DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), invViewProj
	);
	rayDir = DirectX::XMVector3Normalize(rayDir);

	// ���C�Ɠ���̏ꏊ��I�u�W�F�N�g�̏Փ˔���
	bool hit = false;
	DirectX::XMFLOAT3 hitPosition = { 0.0f, 0.0f, 0.0f };
	if (0)
	{
		hit = true;
		hitPosition = {};
		clickCount++;
		TransitionMineState();
	}

	// �f�o�b�O�p���X�V
	DirectX::XMStoreFloat3(&debugClickPosition, rayOrigin);
	std::ostringstream oss;
	oss << "Mouse: (" << mouseX << ", " << mouseY << ")"
		<< " | Ray Origin: (" << debugClickPosition.x << ", " << debugClickPosition.y << ", " << debugClickPosition.z << ")"
		<< " | Count: " << clickCount;
	debugInfo = oss.str();
}
//�z����
// �`�b�v�N���X�p�������N���X���Henum�Ǘ��H
//y�����]������
//����
//8.5x8.5
//chip class�Ŏ擾�ς݂��ǂ����̃t���O

