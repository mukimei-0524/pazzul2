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
	void Update(float elapsedTime);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//�`�b�v�o�^
	void Register(MapChip* chips);

	void Clear();

private:
	//�z��
	std::vector<MapChip*>chips;
};