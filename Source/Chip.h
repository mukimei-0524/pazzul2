#pragma once

#include "Graphics/Model.h"
#include "mapchip.h"

//�Q�[�v���ł����G�l�~�[�X���C��
class Chip :public MapChip
{
public:
	Chip();
	~Chip()override;

	//�X�V����
	void Update(float elapsedTime)override;

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader)override;
private:
	//���f�������
	Model* chips = nullptr;
};