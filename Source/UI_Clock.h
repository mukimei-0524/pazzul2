#pragma once

#include "UI.h"

//�E�㎞�vUI
class Clock :public UI
{
public:
	Clock() {};
	~Clock()override {};

	//������
	void Initialize() override;

	//�I����
	void Finalize() override;

	//�X�V����
	void Update(float elapsedTime) override;

	//�`�揈��
	void Render() override;


	void Miss(float amount)
	{
		angle += amount;
	}

	void SetTimer(int Timer) { this->time = time; }

private:
	Sprite* spr_hands = nullptr;
	Sprite* spr_base = nullptr;

	const float ToRadian = 6.0f;	//1�b �� 6�x
	float angle = 0;

	float Width = 200;		//���\���T�C�Y(��)
	float Height = 200;		//�c�\���T�C�Y(����)

	float positionX = 1050;	//�\���ʒu
	float positionY = 10;

	int time = 0;
};