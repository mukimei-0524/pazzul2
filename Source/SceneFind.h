#pragma once

#include <Graphics/Sprite.h>
#include <Graphics/Graphics.h>

#include "Scene.h"
#include "SceneGame.h"

#include "CameraController.h"
#include "UIManager.h"
#include "mapchip.h"

class SceneFind :public Scene
{
public:
	SceneFind() {};
	~SceneFind() override {};

	//������
	void Initialize() override;

	//�I����
	void Finalize() override;

	//�X�V����
	void Update(float elapsedTime) override;

	//�`�揈��
	void Render() override;


private:
	CameraController* cameraController = nullptr;

	Model* Floor = nullptr;

	std::vector<MapChip*>mapchips;
};


//�n�ʂ̂��邵�̓s�[�X���@�蓖�Ă��n�ʂɂ̂݋L��
