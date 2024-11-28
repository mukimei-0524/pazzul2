#pragma once

#include <vector>
#include "Player.h"
#include "Character.h"

class PlayerManager
{
private:
	PlayerManager() {};
	~PlayerManager() {};

public:
	//�B��̃C���X�^���X�擾	�I�u�U�[�o�[�p�^�[��
	static PlayerManager& Instance()
	{
		static PlayerManager instance;
		return instance;
	}

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//�X�e�[�W�o�^
	void Register(Player* player);

	//�X�e�[�W�S�폜
	void Clear();

	//���C�L���X�g
	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit);

	//�s�[�X���擾
	int GetPlayerCount()const { return static_cast<int>(players.size()); }

	//�s�[�X�擾
	Player* GetPlayer(int index) { return players.at(index); }

private:
	// �z��
	std::vector<Player*> players;
};