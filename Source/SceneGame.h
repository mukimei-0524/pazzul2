#pragma once

#include "Stage.h"
#include "Player.h"
#include "CameraController.h"
#include "Scene.h"
#include "UI_Clock.h"
#include "UIManager.h"
#include <Graphics/Sprite.h>
#include "SceneFind.h"
#include "Audio/Audio.h"


// �Q�[���V�[��
class SceneGame :public Scene
{
public:
	SceneGame() {}
	~SceneGame() override {}

	// ������
	void Initialize() override;

	// �I����
	void Finalize()override;

	// �X�V����
	void Update(float elapsedTime) override;

	// �`�揈��
	void Render() override;

	//�N���b�N�����蔻��
	void HandleClick(ID3D11DeviceContext* dc, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection);

	//�ʒu�擾
	const DirectX::XMFLOAT3& GetPosition()const { return position; }

	//�ʒu�ݒ�
	void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }

	//��]�擾
	const DirectX::XMFLOAT3& GetAngle()const { return angle; }

	//��]�ݒ�
	void setAngle(const DirectX::XMFLOAT3& angle) { this->angle = angle; }

	//bool IsPositionCorrect(Player* player, const DirectX::XMFLOAT3& clickPos);

protected:
	DirectX::XMFLOAT3		position = { 0,0,0 };
	DirectX::XMFLOAT3		angle = { 0,0,0 };
	DirectX::XMFLOAT4X4		transform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	std::vector<DirectX::XMFLOAT3> positions = {
	{-25.0f, 0.0f, -25.0f},
	{-15.0f, 0.0f,-30.0f},
	{0.0f, 0.0f,-25.0f},
	{18.0f, 0.0f,-20.0f},
	{38.0f, 0.0f,-20.0f}
	};
private:

	CameraController* cameraController = nullptr;

	Sprite* Memo = nullptr;
	Sprite* Memo_2 = nullptr;

	Clock* clock = nullptr;

	Model* desk = nullptr;

	std::unique_ptr<AudioSource>BGM_game;

	std::vector<Player*> pieces; // �s�[�X���Ǘ����郊�X�g
	int currentPieceIndex = 0;   // ���݂̐����s�[�X�̃C���f�b�N�X
};
