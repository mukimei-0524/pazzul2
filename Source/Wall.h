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

	//�s��X�V����
	void UpdateTransform();

protected:
	DirectX::XMFLOAT3		position = { 0,0,0 };
	DirectX::XMFLOAT3		angle = { 0,0,0 };
	DirectX::XMFLOAT3		scale = { 1,1,1 };
	DirectX::XMFLOAT4X4		transform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

private:
	//���f�������
	Model* model = nullptr;
};