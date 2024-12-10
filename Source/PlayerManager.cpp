#include "PlayerManager.h"
#include "Input/Input.h"


void PlayerManager::Update(float elapsedTime)
{
	for (Player* player : players)
	{
		player->Update(elapsedTime);
	}
	// マウスの位置からレイを生成
	int mouseX = Input::Instance().GetMouse().GetPositionX(); // マウスのX位置
	int mouseY = Input::Instance().GetMouse().GetPositionY(); // マウスのY位置

	DirectX::XMFLOAT3 rayStart = { static_cast<float>(mouseX), static_cast<float>(mouseY), 0.0f };
	DirectX::XMFLOAT3 rayEnd = { static_cast<float>(mouseX), static_cast<float>(mouseY), 1.0f };
	
	Mouse& mouse = Input::Instance().GetMouse();

	// クリックがあった場合に選択
	if (mouse.GetButtonDown() & Mouse::BTN_LEFT)  // 左クリック
	{
		SelectPlayer(rayStart, rayEnd);
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

void PlayerManager::SelectPlayer(const DirectX::XMFLOAT3& rayStart, const DirectX::XMFLOAT3& rayEnd)
{
	HitResult hitResult;
	// レイキャストで当たったプレイヤーを取得
	if (RayCast(rayStart, rayEnd, hitResult))
	{
		Player* selectedPlayer = static_cast<Player*>(hitResult.hitPlayer);
		// すでに選択されている場合は選択解除、選択されていなければ選択
		if (selectedPlayer->IsSelected())
		{
			selectedPlayer->SetAlpha(1.0f);  // 透明度を元に戻す
			selectedPlayer->SetSelected(false);
		}
		else
		{
			selectedPlayer->SetAlpha(0.5f);  // 透明度を変更
			selectedPlayer->SetSelected(true);
		}
	}
}
