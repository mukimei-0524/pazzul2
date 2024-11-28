#include "mapchip.h"

void MapChip::Update(float elapsedTime)
{
	
}

void MapChip::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, chips);
}


