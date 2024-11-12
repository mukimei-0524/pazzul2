#include "EnemyManager.h"
#include "Enemy.h"
#include "Graphics/Graphics.h"
#include "Collision.h"

//�X�V����
void EnemyManager::Update(float elapsedTime)
{
	//��enemies�͈̔�for���̒���erase()����ƕs����������Ă��܂�����
	for (Enemy* enemy : enemies)
	{
		enemy->Update(elapsedTime);
	}

	//�j������
	for (Enemy* enemy : removes)
	{
		//std::vector����v�f���폜����ꍇ�̓C�e���[�^�[�ō폜���Ȃ���΂Ȃ�Ȃ�
		std::vector<Enemy*>::iterator it = std::find(enemies.begin(), enemies.end(), enemy);

		if (it != enemies.end())
		{
			enemies.erase(it);
		}

		//�e�ۂ̔j������
		delete enemy;
	}
	//�j�����X�g���N���A
	removes.clear();

	//�G���m�̏Փˏ���
	CollisionEnemyVsEnemies();

}

//�`�揈��
void EnemyManager::Render(ID3D11DeviceContext* context, Shader* shader)
{
	for (Enemy* enemy : enemies)
	{
		enemy->Render(context, shader);
	}
}

//�G�l�~�[�o�^
void EnemyManager::Register(Enemy* enemy)
{
	enemies.emplace_back(enemy);
}

//�G�l�~�[�S�폜
void EnemyManager::Clear()
{
	for (Enemy* enemy : enemies)
	{
		delete enemy;
	}
	enemies.clear();
}

//�f�o�b�O�v���~�e�B�u�`��
void EnemyManager::DrawDebugPrimitive()
{
	//DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//�Փ˔���p�̃f�o�b�O����`��
	//debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
}

//�G�l�~�[�폜
void EnemyManager::Remove(Enemy* enemy)
{
	removes.insert(enemy);
}

//�G�l�~�[���m�̏Փˏ���
void EnemyManager::CollisionEnemyVsEnemies()
{
	size_t enemyCount = enemies.size();
	for (int i = 0; i < enemyCount; ++i)
	{
		Enemy* enemyA = enemies.at(i);
		for (int j = i + 1; j < enemyCount; ++j)
		{
			Enemy* enemyB = enemies.at(j);
			DirectX::XMFLOAT3 outPosition;
			if (Collision::IntersectSphereVsSphere(
				enemyA->GetPosition(),
				enemyA->GetRadius(),
				enemyB->GetPosition(),
				enemyB->GetRadius(),
				outPosition
				))
			{
				//�����o����̈ʒu�ݒ�
				enemyB->SetPosition(outPosition);
			}
		}
	}
}

