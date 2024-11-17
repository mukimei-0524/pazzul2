#pragma once

#include <DirectXMath.h>

//�J�����R���g���[���[
class CameraController
{
public:
	CameraController() {};
	~CameraController() {};

	//�X�V����
	void Update(float elapsedTime);

	//�^�[�Q�b�g�ʒu�ݒ�
	void SetTarget(const DirectX::XMFLOAT3& target) { this->target = target; }

private:
	DirectX::XMFLOAT3 target = { 0,0,0 };
	DirectX::XMFLOAT3 angle = { 0,0,0 };
	float range = 10.0f;
};