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
