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

protected:
	DirectX::XMFLOAT3		position = { 0,0,0 };
	DirectX::XMFLOAT3		angle = { 0,0,0 };
	DirectX::XMFLOAT4X4		transform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

private:

	CameraController* cameraController = nullptr;

	Sprite* gauge = nullptr;

	Sprite* tentative_UI = nullptr;

	Clock* clock = nullptr;

	Model* desk = nullptr;

	std::unique_ptr<AudioSource>BGM_game;
};
