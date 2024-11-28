#pragma once

#include <DirectXMath.h>

//キャラクター
class Character
{
public:
	Character() {}
	virtual ~Character() {}

	//行列更新処理
	void UpdateTransform();

public:
	//位置取得
	const DirectX::XMFLOAT3& GetPosition()const { return position; }
	
	//位置設定
	void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }
	
	//回転取得
	const DirectX::XMFLOAT3& GetAngle()const { return angle; }

	//回転設定
	void setAngle(const DirectX::XMFLOAT3& angle) { this->angle = angle; }

	//スケール取得
	const DirectX::XMFLOAT3& GetScale()const { return scale; }

	//スケール設定
	void setScale(const DirectX::XMFLOAT3& scale) { this->scale = scale; }

	//半径取得
	float GetRadius()const { return radius; }

	// モデルのアルファ値を設定
	void SetAlpha(float alpha) { this->alpha = alpha; }

protected:
	DirectX::XMFLOAT3		position = { 0,0,0 };
	DirectX::XMFLOAT3		angle = { 0,0,0 };
	DirectX::XMFLOAT3		scale = { 1,1,1 };
	DirectX::XMFLOAT4X4		transform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	float radius = 0.5f;

	// モデルのアルファ値
	float alpha = 1.0f;
};