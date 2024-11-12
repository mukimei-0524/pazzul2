#pragma once

#include "Stage.h"
#include "Player.h"
#include "CameraController.h"
#include "Scene.h"
#include <Graphics/Sprite.h>

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

private:
	void HandleClick(int x, int y);

private:
	Player* player = nullptr;
	CameraController* cameraController = nullptr;

	Sprite* gauge = nullptr;
};
