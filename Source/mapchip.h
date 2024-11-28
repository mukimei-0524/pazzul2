#pragma once

#include "Character.h"
#include "Graphics/Graphics.h"

//�N���X�͑S�̂̂��Ƃł͂Ȃ��̂��Ƃ�����
class MapChip:public Character
{
public:
	enum class CHIPS	//�}�b�v�`�b�v�̎��
	{
		WITH,		//�O�F�󂠂�(�����炪���܂��Ă���)
		WHITHOUT	//�P�F��Ȃ�(�����炪���܂��Ă��Ȃ�)
	};

public:
	MapChip() {};
	~MapChip() override {};

	//�X�V����
	virtual void Update(float elapsedTime) = 0;

	//�`�揈��
	virtual void Render(ID3D11DeviceContext* dc, Shader* shader) = 0;

private:
	Model* chips = nullptr;
};