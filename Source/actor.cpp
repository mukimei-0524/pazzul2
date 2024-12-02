#include "Input/Input.h"
#include "Graphics/Graphics.h"

#include "actor.h"

Actor::Actor()
{
	model = new Model("Data/Model/team/MDL/Character_jump.mdl");
	//model->PlayAnimation(1, true);
}

Actor::~Actor()
{
	delete model;
}

void Actor::Update(float elapsedTime)
{
	//���[�V���������Ȃ��̂Ō�������
	//�G���^�[�����Ń����V���b�g�A�j���[�V�����Đ�(�̂��Ƀ}�E�X�őI�������}�X�ɐi�߂鏈���ɕύX)
	GamePad& gamePad = Input::Instance().GetGamePad();
	if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT)
	{
		model->PlayAnimation(0, true);
	}

	//���f���A�j���[�V�����X�V����
	model->UpdateAnimation(elapsedTime);

	//���f���s��X�V
	model->UpdateTransform(transform);
}

void Actor::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);
}
