#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Character.h"
#include "Effect.h"
#include "Collision.h"

//�v���C���[
class Player :public Character
{
public:
	Player();
	~Player() override;

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//�f�o�b�O�pGUI�`��
	void DrawDebugGUI();

	//�f�o�b�O�v���~�e�B�u�`��
	void DrawDebugPrimitive();

	//�W�����v���͏���
	void InputJump();

	// ���C�L���X�g
	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit);

	// �C���X�^���g�擾
	static Player& Instance();

protected:
	//���n�����Ƃ��ɌĂ΂��
	void OnLanding() override;

private:
	Model* model = nullptr;
	Effect* hitEffect = nullptr;
	float turnSpeed = DirectX::XMConvertToRadians(720);
	float moveSpeed = 5.0f;

	float jumpSpeed = 20.0f;
	
	int jumpCount = 0;
	int jumpLimit = 2;

	//�X�e�B�b�N���͒l����ړ��x�N�g�����擾
	DirectX::XMFLOAT3 GetMoveVec() const;

	//���͏���
	void InputMove(float elapsedTime);
};

//elapsedTime:�o�ߎ���