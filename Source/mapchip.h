#pragma once

#include "Character.h"
#include "Graphics/Graphics.h"

//�N���X�͑S�̂̂��Ƃł͂Ȃ��̂��Ƃ�����
//�Q�[�v���ł����G�l�~�[
class MapChip:public Character
{
public:
	MapChip() {};
	~MapChip()override {};

	//�X�V����
	virtual void Update(float elapsedTime) = 0;

	//�`�揈��
	virtual void Render(ID3D11DeviceContext* dc, Shader* shader) = 0;

	void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }

};