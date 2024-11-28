#pragma once

#include <Graphics/Sprite.h>
#include <Graphics/Graphics.h>

#include "Scene.h"
#include "SceneGame.h"

#include "CameraController.h"
#include "UIManager.h"
#include "mapchip.h"

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
	CameraController* cameraController = nullptr;

	Model* Floor = nullptr;

	std::vector<MapChip*>mapchips;
};


//地面のしるしはピースが掘り当てた地面にのみ記載
