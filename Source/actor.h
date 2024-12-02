#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"

#include "Character.h"
//�v���C���[�̓����A�A�j���[�V������

class Actor :public Character
{
public:
	Actor();
	~Actor() override;

	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

private:
	Model* model = nullptr;
};