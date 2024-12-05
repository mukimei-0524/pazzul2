#pragma once

#include <DirectXMath.h>

//パズル画面カメラコントローラー
class CameraController
{
public:
	CameraController() {};
	~CameraController() {};

	//更新処理
	void Update(float elapsedTime);

	//ターゲット位置設定
	void SetTarget(const DirectX::XMFLOAT3& target) { this->target = target; }

private:
	DirectX::XMFLOAT3 target = { 0,0,0 };
	DirectX::XMFLOAT3 angle = { DirectX::XMConvertToRadians(45),0,0 };
	float rollSpeed = DirectX::XMConvertToRadians(90);
	float range = 75.0f;


	float maxAngleX = DirectX::XMConvertToRadians(60);
	float minAngleX = DirectX::XMConvertToRadians(30);
};