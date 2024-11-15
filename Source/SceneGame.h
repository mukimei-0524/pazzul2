#pragma once

#include "Stage.h"
#include "Player.h"
#include "CameraController.h"
#include "Scene.h"
#include <Graphics/Sprite.h>

// ゲームシーン
class SceneGame :public Scene
{
public:
	SceneGame() {}
	~SceneGame() override {}

	// 初期化
	void Initialize() override;

	// 終了化
	void Finalize()override;

	// 更新処理
	void Update(float elapsedTime) override;

	// 描画処理
	void Render() override;

private:
	void HandleClick(int x, int y);

private:
	Player* player = nullptr;
	CameraController* cameraController = nullptr;

	Sprite* gauge = nullptr;
};
