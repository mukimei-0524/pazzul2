#pragma once

#include "Input/Input.h"
#include "Graphics/Sprite.h"
#include "Scene.h"
#include "Audio/Audio.h"

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
	//Model* currentModel = nullptr;
	Sprite* stage_1 = nullptr;		//名前変える
	Sprite* stage_2 = nullptr;		//名前変える
	Sprite* stage_3 = nullptr;		//名前変える
	Sprite* start = nullptr;
	Sprite* back = nullptr;
	Sprite* spr_back = nullptr;

	std::unique_ptr<AudioSource>BGM_select;
	std::unique_ptr<AudioSource>SE_button;
};