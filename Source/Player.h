#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Character.h"
#include "Effect.h"
#include "Collision.h"
#include "PlayerManager.h"

//player���s�[�X�Ƃ���
//�v���C���[
class Player :public Character
{
public:
	Player(const char* filename);
	~Player() override;

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//�f�o�b�O�pGUI�`��
	void DrawDebugGUI();

	// ���C�L���X�g
	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit);

	// �C���X�^���g�擾
	//static Player& Instance();

private:
	Model* model = nullptr;

	//�v���C���[�̃C���f�b�N�X�擾
	//PlayerManager& playerManager = PlayerManager::Instance();
	//int playerCount = playerManager.GetPlayerCount();
	//Player* player = playerManager.GetPlayer(i);

	//�X�e�B�b�N���͒l����ړ��x�N�g�����擾
	DirectX::XMFLOAT3 GetMoveVec() const;
};