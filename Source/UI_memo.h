#pragma once

#include "UI.h"
#include "UIManager.h"

class UI_Memo :public UI
{
public:
	UI_Memo() {};
	~UI_Memo()override {};

	//������
	void Initialize() override;

	//�I����
	void Finalize() override;

	//�X�V����
	void Update(float elapsedTime) override;

	//�`�揈��
	void Render() override;

private:
	Sprite* spr_Map = nullptr;
	Sprite* spr_MapUI = nullptr;

	float Width = 200;		//���\���T�C�Y(��)
	float Height = 200;		//�c�\���T�C�Y(����)

	float positionX = 1050;	//�\���ʒu
	float positionY = 10;

};