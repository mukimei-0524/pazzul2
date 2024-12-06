#include "Wall.h"

Wall::Wall()
{
	model = new Model("Data/Model/team/MDL/Wall.mdl");
}

Wall::~Wall()
{
	delete model;
}

void Wall::Update(float elapsedTime)
{

}

void Wall::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);
}
