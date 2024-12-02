#pragma once

#include "Graphics/Model.h"

#include "mapchip.h"
#include "Collision.h"

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

	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit);

private:
	//���f�������
	Model* chips = nullptr;
};