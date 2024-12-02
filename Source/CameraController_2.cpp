#include "Cameracontroller_2.h"
#include "camera.h"
#include "Input/Input.h"

//�X�V����
void CameraController_2::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisRX();
	float ay = gamePad.GetAxisRY();

	//�J�����̉�]���x
	float speed = rollSpeed * elapsedTime;

	//�X�e�B�b�N�̓��͒l�ɍ��킹��X����Y������]
	angle.x += ay * speed;	//angle.x x����](�c��)�ɃX�e�B�b�Ny����](�c��)
	angle.y += ax * speed;	//angle.y y����](����)�ɃX�e�B�b�Nx����](����)

	//�J������]�l����]�s��ɕϊ�
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	//��]�s�񂩂�O�����x�N�g�������o��
	DirectX::XMVECTOR Front = Transform.r[2];
	DirectX::XMFLOAT3 front;
	DirectX::XMStoreFloat3(&front, Front);

	//�����_������x�N�g�������Ɉ�苗�����ꂽ�J�������_�����߂�
	DirectX::XMFLOAT3 eye;
	eye.x = front.x * range;
	eye.y = front.y * range + 160.0f;
	eye.z = front.z * range + 100.0f;

	//�J�����̎��_�ƒ����_��ݒ�
	Camera::Instance().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
}
