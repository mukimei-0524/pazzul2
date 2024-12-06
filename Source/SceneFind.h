#pragma once

#include <Graphics/Sprite.h>
#include <Graphics/Graphics.h>

#include "Scene.h"
#include "SceneGame.h"

#include "CameraController_2.h"
#include "UIManager.h"
#include "mapchip.h"
#include "actor.h"
#include "UI_memo.h"
#include "Wall.h"

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

	//時間取得
	int GetTimer() { return timer; }

	//位置設定
	int SetTimer() { this->timer = timer; }

	int timer = 0;

private:
	CameraController_2* cameraController_2 = nullptr;

	Actor* actor = nullptr;

	UI_Memo* memo = nullptr;

	Wall* wall = nullptr;

	std::vector<MapChip*>mapchips;

};
//タイル1つ２３くらい

//UIとピースの結び付け	3D:スライムクリック生成参考
//地面の指定の場所にピースを設定する方法
//できるなら時間の継続方法
// 
// 
//ステージの分け方

//リファクタリングする
//マウス操作のボタンの当たり判定関数化(独立化)