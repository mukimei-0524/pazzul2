#pragma once
#include "UI.h"

class UI_Rock1:public UI
{
public:
	UI_Rock1() {};
	~UI_Rock1() override {};

	void Initialize() override;

	void Finalize() override;

	void Update(float elapsedTime) override;

	void Render() override;

private:
	struct Object
	{
		DirectX::XMFLOAT3		scale_velocity = { 0,0,0 };
		DirectX::XMFLOAT3		position = { 0,0,0 };
		DirectX::XMFLOAT3		angle = { 0,0,0 };
		DirectX::XMFLOAT3		scale = { 0,0,0 };
		bool	exist = true;
		bool	isPlay = false;

		Sprite* spr_obj = nullptr;
		float tx, ty;
	};
	Object		objs[5];

private:
	float angle = 0;

	//最小係数
	float minCoefficient = -0.2f;

	// スケーリングの最低値
	float minScaling = 0.5f;
};