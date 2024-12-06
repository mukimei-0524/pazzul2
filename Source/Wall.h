#pragma once
#include "mapchip.h"

class Wall :public MapChip
{
public:
	Wall();
	~Wall()override;

	//XVˆ—
	void Update(float elapsedTime)override;

	//•`‰æˆ—
	void Render(ID3D11DeviceContext* dc, Shader* shader)override;

private:
	//ƒ‚ƒfƒ‹“ü‚ê‚é
	Model* model = nullptr;
};