#pragma once

#include "Input/Input.h"
#include "Graphics/Sprite.h"
#include "Scene.h"

//タイトルシーン
class SceneSelect :public Scene
{
public:
	SceneSelect() {};
	~SceneSelect() override {};

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
		Tutorial,
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
	Stage stage = Tutorial;
	Model* currentModel = nullptr;
	Sprite* tutorial = nullptr;		//名前変える
	Sprite* stage1 = nullptr;		//名前変える
	Sprite* stage2 = nullptr;		//名前変える
	Sprite* stage3 = nullptr;		//名前変える
	Sprite* start = nullptr;
	Sprite* right = nullptr;  // 四角のスプライト
	Sprite* left = nullptr;  // 四角のスプライト
	Sprite* back = nullptr;  
	RECT leftRect;
	RECT rightRect;

};