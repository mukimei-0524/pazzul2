#pragma once

#include <vector>
#include <set>
#include "Projectile.h"

//�e�ۃ}�l�[�W���[
class ProjectileManager
{
public:
	ProjectileManager();
	~ProjectileManager();

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//�f�o�b�O�v���~�e�B�u�`��
	void DrawDebugPrimitive();

	//�e�ۓo�^
	void Rigister(Projectile* projectile);

	//�e�ۑS�폜
	void Clear();

	//�e�ۍ폜
	void Remove(Projectile* projectile);

	//�e�ې��擾
	int GetProjectileCount()const { return static_cast<int>(projectiles.size()); }

	//�e�ێ擾
	Projectile* GetProjectile(int index) { return projectiles.at(index); }

private:
	std::vector<Projectile*> projectiles;
	std::set<Projectile*> removes;
};