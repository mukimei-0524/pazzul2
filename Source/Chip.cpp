#include "Chip.h"

Chip::Chip()
{
	chips = new Model("Data/Model/team/MDL/Floor.mdl");
}

Chip::~Chip()
{
	delete chips;
}

void Chip::Update(float elapsedTime)
{
	UpdateTransform();

	chips->UpdateTransform(transform);
}

void Chip::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, chips);
}

bool Chip::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
	return Collision::IntersectRayVsModel(start, end, chips, hit);
}
