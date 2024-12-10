#pragma once

#include "Scene.h"
#include "SceneFind.h"

class SceneManager
{
private:
	SceneManager() {};
	~SceneManager() {};

public:
	//唯一のインスタンス取得
	static SceneManager&Instance()
	{
		static SceneManager instance;
		return instance;
	}

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render();

	//シーンクリア
	void Clear();

	//シーン切り替え
	void ChangeScene(Scene* scene);

	// 時間設定
	void SetTimer(int time) { this->timer = time; }

	// 時間取得
	int GetTimer() { return timer; }

private:
	Scene* currentScene = nullptr;
	Scene* nextScene = nullptr;

	float timer = 0.0f;
};

//currentScene：現在のシーン