#pragma once

#include "Graphics/Graphics.h"
#include "Projectile.h"

//���i�e��
class ProjectileStraight :public Projectile
{
public:
	//ProjectileStraight();
	ProjectileStraight(ProjectileManager* manager);
	~ProjectileStraight() override;		//�p��������I�[�o�[���C�h

	//�X�V����
	void Update(float elapsedTime) override;

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader) override;

	//����
	void Launch(const DirectX::XMFLOAT3& direction,
				const DirectX::XMFLOAT3& position
				);

private:
	Model* model = nullptr;
	float speed = 10.0f;
	float lifeTimer = 3.0f;
};