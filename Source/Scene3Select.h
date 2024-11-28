#pragma once

#include "Input/Input.h"
#include "Graphics/Sprite.h"
#include "Scene.h"

//タイトルシーン
class Scene3Select :public Scene
{
public:
	Scene3Select() {};
	~Scene3Select() override {};

	//初期化
	void Initialize() override;

	//終了化
	void Finalize() override;

	//更新処理
	void Update(float elapsedTime) override;

	//描画処理
	void Render() override;

private:
	enum Stage
	{
		Stage1,
		Stage2,
		Stage3,
	};

	DirectX::XMFLOAT3     position = { 0,-1,0 };
	DirectX::XMFLOAT3     angle = { 0,135,0 };
	DirectX::XMFLOAT3     scale = { 1,1,1 };

	DirectX::XMFLOAT4X4   transform =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	void HandleClick(int x, int y);
private:
	Stage stage = Stage1;
	//Model* currentModel = nullptr;
	Sprite* stage1 = nullptr;		//名前変える
	Sprite* stage2 = nullptr;		//名前変える
	Sprite* stage3 = nullptr;		//名前変える
	Sprite* start = nullptr;
	Sprite* back = nullptr;
};