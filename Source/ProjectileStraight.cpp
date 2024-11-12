#include "ProjectileStraight.h"

//�R���X�g���N�^
ProjectileStraight::ProjectileStraight(ProjectileManager* manager)
	:Projectile(manager)
{
	//model = new Model("Data/Model/SpikeBall/SpikeBall.mdl");
	model = new Model("Data/Model/Sword/Sword.mdl");

	//�\���T�C�Y����
	//scale.x = scale.y = scale.z = 0.5f;
	scale.x = scale.y = scale.z = 3.0f;
}

//�f�X�g���N�^
ProjectileStraight::~ProjectileStraight()
{
	delete model;
}

//�X�V����
void ProjectileStraight::Update(float elapsedTime)
{
	//�ړ�
	float speed = this->speed * elapsedTime;
	position.x += direction.x * speed;
	position.z += direction.z * speed;

	//�I�u�W�F�N�g�s����X�V
	UpdateTransform();

	//���f���s��X�V
	model->UpdateTransform(transform);

	//��������
	lifeTimer -= elapsedTime;
	if (lifeTimer <= 0.0f)
	{
		//�������폜
		Destroy();
	}
}

//�`�揈��
void ProjectileStraight::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);
}

//����
void ProjectileStraight::Launch(const DirectX::XMFLOAT3& direction, const DirectX::XMFLOAT3& position)
{
	this->direction = direction;
	this->position = position;
}
