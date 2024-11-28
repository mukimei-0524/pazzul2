#pragma once

#include <vector>
#include "mapchip.h"

class ChipManager
{
private:
	ChipManager() {};
	~ChipManager() {};

public:
	//�B��̃C���X�^���X�擾
	static ChipManager& Instance()
	{
		static ChipManager instance;
		return instance;
	}

	//�X�V����
	void Update(float elapsedTIme);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

private:
	std::vector<MapChip*>chips;


};