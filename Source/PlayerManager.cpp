#include "PlayerManager.h"


void PlayerManager::Update(float elapsedTime)
{
	for (Player* player : players)
	{
		player->Update(elapsedTime);
	}
}

void PlayerManager::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	for (Player* player : players)
	{ 
		player->Render(dc, shader);
	}
}

void PlayerManager::Register(Player* player)
{
	players.emplace_back(player);
}

void PlayerManager::Clear()
{
	for (Player* player : players)
	{
		delete player;
	}
	//イテレーターをクリアにする
	players.clear();
}

bool PlayerManager::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
	bool result = false;

	hit.distance = FLT_MAX;

	for (Player* player : players)
	{
		HitResult tmp;
		if (player->RayCast(start, end, tmp))
		{
			if (hit.distance > tmp.distance)
			{
				hit = tmp;
				hit.hitPlayer = player;
				result = true;
			}
		}

	}

	return result;
}
