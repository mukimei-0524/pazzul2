#pragma once

#include <Graphics/Sprite.h>
#include <Graphics/Graphics.h>

#include "Scene.h"
#include "SceneGame.h"

#include "CameraController_2.h"
#include "UIManager.h"
#include "mapchip.h"
#include "actor.h"
#include "UI_memo.h"
#include "Wall.h"

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

	//���Ԏ擾
	int GetTimer() { return timer; }

	//�ʒu�ݒ�
	int SetTimer() { this->timer = timer; }

	int timer = 0;

private:
	CameraController_2* cameraController_2 = nullptr;

	Actor* actor = nullptr;

	UI_Memo* memo = nullptr;

	Wall* wall = nullptr;

	std::vector<MapChip*>mapchips;

};
//�^�C��1�Q�R���炢

//UI�ƃs�[�X�̌��ѕt��	3D:�X���C���N���b�N�����Q�l
//�n�ʂ̎w��̏ꏊ�Ƀs�[�X��ݒ肷����@
//�ł���Ȃ玞�Ԃ̌p�����@
// 
// 
//�X�e�[�W�̕�����

//���t�@�N�^�����O����
//�}�E�X����̃{�^���̓����蔻��֐���(�Ɨ���)