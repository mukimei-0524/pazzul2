#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"

#include "Character.h"
//プレイヤーの動き、アニメーション等

class Actor :public Character
{
public:
	Actor();
	~Actor() override;

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	DirectX::XMFLOAT3 GetMoveVec() const;

private:	
	Model* model = nullptr;

	float moveLength = 11.0f;
};