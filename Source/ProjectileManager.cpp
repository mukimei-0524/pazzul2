#include "ProjectileManager.h"
#include "Graphics/Graphics.h"


//コンストラクタ
ProjectileManager::ProjectileManager()
{
}

//デストラクタ
ProjectileManager::~ProjectileManager()
{
	Clear();
}

//更新処理
void ProjectileManager::Update(float elapsedTime)
{
	//更新処理
	for (Projectile* projectile :projectiles)
	{
		projectile->Update(elapsedTime);
	}

	//破棄処理
	//※projectilesの範囲for文中でerase()とすると不具合が発生してしまうため
	//更新処理が終わった後に破棄リストに積まれたオブジェクトを削除する

	for (Projectile* projectile : removes)
	{
		//std::vectorから要素を削除する場合はイテレーターで削除しなければならない
		std::vector<Projectile*>::iterator it = std::find(projectiles.begin(), projectiles.end(), projectile);

		if (it != projectiles.end())
		{
			projectiles.erase(it);
		}

		//弾丸の破棄処理
		delete projectile;
	}
	//破棄リストをクリア
	removes.clear();
}

//描画処理
void ProjectileManager::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	for (Projectile* projectile : projectiles)
	{
		projectile->Render(dc, shader);
	}
}

//デバッグプリミティブ描画
void ProjectileManager::DrawDebugPrimitive()
{
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
}

//弾丸登録
void ProjectileManager::Rigister(Projectile* projectile)
{
	projectiles.emplace_back(projectile);
}

//弾丸全削除
void ProjectileManager::Clear()
{
	projectiles.clear();
}

void ProjectileManager::Remove(Projectile* projectile)
{
	removes.insert(projectile);
}
