#pragma once

#include <Graphics/Sprite.h>
#include <Graphics/Graphics.h>

#include "Scene.h"
#include "SceneGame.h"

#include "CameraController_2.h"
#include "UIManager.h"
#include "mapchip.h"
#include "actor.h"

class SceneFind :public Scene
{
public:
	SceneFind() {};
	~SceneFind() override {};

	//初期化
	void Initialize() override;

	//終了化
	void Finalize() override;

	//更新処理
	void Update(float elapsedTime) override;

	//描画処理
	void Render() override;


private:
	CameraController_2* cameraController_2 = nullptr;

	Model* Floor = nullptr;

	Actor* actor = nullptr;

	std::vector<MapChip*>mapchips;

	const float CHIP_SIZE = 5.0f;		//チップ一つのサイズ
};

//地面のしるしはピースが掘り当てた地面にのみ記載

//タイル1つ２３くらい
