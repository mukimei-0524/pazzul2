#include "PlayerManager.h"
#include "Input/Input.h"


void PlayerManager::Update(float elapsedTime)
{
	for (Player* player : players)
	{
		player->Update(elapsedTime);
	}
	// �}�E�X�̈ʒu���烌�C�𐶐�
	int mouseX = Input::Instance().GetMouse().GetPositionX(); // �}�E�X��X�ʒu
	int mouseY = Input::Instance().GetMouse().GetPositionY(); // �}�E�X��Y�ʒu

	DirectX::XMFLOAT3 rayStart = { static_cast<float>(mouseX), static_cast<float>(mouseY), 0.0f };
	DirectX::XMFLOAT3 rayEnd = { static_cast<float>(mouseX), static_cast<float>(mouseY), 1.0f };
	
	Mouse& mouse = Input::Instance().GetMouse();

	// �N���b�N���������ꍇ�ɑI��
	if (mouse.GetButtonDown() & Mouse::BTN_LEFT)  // ���N���b�N
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
	//�C�e���[�^�[���N���A�ɂ���
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
	// ���C�L���X�g�œ��������v���C���[���擾
	if (RayCast(rayStart, rayEnd, hitResult))
	{
		Player* selectedPlayer = static_cast<Player*>(hitResult.hitPlayer);
		// ���łɑI������Ă���ꍇ�͑I�������A�I������Ă��Ȃ���ΑI��
		if (selectedPlayer->IsSelected())
		{
			selectedPlayer->SetAlpha(1.0f);  // �����x�����ɖ߂�
			selectedPlayer->SetSelected(false);
		}
		else
		{
			selectedPlayer->SetAlpha(0.5f);  // �����x��ύX
			selectedPlayer->SetSelected(true);
		}
	}
}
