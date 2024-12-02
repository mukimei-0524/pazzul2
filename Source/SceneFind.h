#pragma once

#include <Graphics/Sprite.h>
#include <Graphics/Graphics.h>

#include "Scene.h"
#include "SceneGame.h"

#include "CameraController_2.h"
#include "UIManager.h"
#include "mapchip.h"
#include "actor.h"

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
	CameraController_2* cameraController_2 = nullptr;

	Model* Floor = nullptr;

	Actor* actor = nullptr;

	std::vector<MapChip*>mapchips;

	const float CHIP_SIZE = 5.0f;		//�`�b�v��̃T�C�Y
};

//�n�ʂ̂��邵�̓s�[�X���@�蓖�Ă��n�ʂɂ̂݋L��

//�^�C��1�Q�R���炢
