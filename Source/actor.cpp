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
	//モーション動かないので原因究明
	//エンター押下でワンショットアニメーション再生(のちにマウスで選択したマスに進める処理に変更)
	GamePad& gamePad = Input::Instance().GetGamePad();
	if (gamePad.GetButtonDown() & GamePad::BTN_RIGHT)
	{
		model->PlayAnimation(0, true);
	}

	//モデルアニメーション更新処理
	model->UpdateAnimation(elapsedTime);

	//モデル行列更新
	model->UpdateTransform(transform);
}

void Actor::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);
}
