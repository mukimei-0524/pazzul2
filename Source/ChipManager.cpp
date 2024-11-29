#include "ChipManager.h"

void ChipManager::Update(float elapsedTime)
{
	for (MapChip* mapChip : chips)
	{
		mapChip->Update(elapsedTime);
	}
}

void ChipManager::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	for (MapChip* mapChip : chips)
	{
		mapChip->Render(dc, shader);
	}
}

void ChipManager::Register(MapChip* chip)
{
	chips.emplace_back(chip);
}

void ChipManager::Clear()
{
	for (MapChip* mapChip : chips)
	{
		delete mapChip;
	}
	chips.clear();
}
