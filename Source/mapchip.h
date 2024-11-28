#pragma once

#include "Character.h"
#include "Graphics/Sprite.h"

class MapChip:public Character
{
public:
	enum class CHIPS	//�}�b�v�`�b�v�̎��
	{
		WITH,		//�O�F�󂠂�(�����炪���܂��Ă���)
		WHITHOUT	//�P�F��Ȃ�(�����炪���܂��Ă��Ȃ�)
	};

public:
	MapChip();
	~MapChip() override {};

	void Update(float elapsedTime);

	void Render();

private:
	DirectX::XMFLOAT2 position{ 0,0 };

	Sprite* chips = nullptr;
};