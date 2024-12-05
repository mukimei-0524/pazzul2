#pragma once

#include "UI.h"
#include "UIManager.h"

class UI_Memo_Switch :public UI
{
public:
	UI_Memo_Switch() {};
	~UI_Memo_Switch()override {};

	//������
	void Initialize() override;

	//�I����
	void Finalize() override;

	//�X�V����
	void Update(float elapsedTime) override;

	//�`�揈��
	void Render() override;

private:
	Sprite* Spr_Memo_Switch = nullptr;

	float Width = 200;		//���\���T�C�Y(��)
	float Height = 200;		//�c�\���T�C�Y(����)

	float positionX = 1050;	//�\���ʒu
	float positionY = 10;

};