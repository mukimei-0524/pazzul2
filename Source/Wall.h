#pragma once
#include "mapchip.h"

class Wall :public MapChip
{
public:
	Wall();
	~Wall()override;

	//�X�V����
	void Update(float elapsedTime)override;

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader)override;

private:
	//���f�������
	Model* model = nullptr;
};