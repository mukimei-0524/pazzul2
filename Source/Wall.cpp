#include "Wall.h"

Wall::Wall()
{
	model = new Model("Data/Model/team/MDL/Wall.mdl");
	scale.x = scale.y = scale.z = 0.67f;
}

Wall::~Wall()
{
	delete model;
}

void Wall::Update(float elapsedTime)
{
	UpdateTransform();

	model->UpdateTransform(transform);
}

void Wall::UpdateTransform()
{
	//�X�P�[���s����쐬
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

	//��]�s����쐬
	//DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

	DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(angle.x);
	DirectX::XMMATRIX Y = DirectX::XMMatrixRotationY(angle.y);
	DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(angle.z);
	DirectX::XMMATRIX R = Y * X * Z;

	//�ʒu�s����쐬
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//3�̍s���g�ݍ��킹�A���[���h�s����쐬
	DirectX::XMMATRIX W = S * R * T;

	//�v�Z�������[���h�s������o��
	DirectX::XMStoreFloat4x4(&transform, W);
}

void Wall::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);
}