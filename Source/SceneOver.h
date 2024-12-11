#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"
#include "Audio/Audio.h"

//タイトルシーン
class SceneOver :public Scene 
{
public:
    SceneOver() {}
    ~SceneOver() override {}

    //初期化
    void Initialize() override;

    //終了化
    void Finalize() override;

    //更新処理
    void Update(float elapsedTime) override;

    //描画処理
    void Render() override;

private:
    Sprite* sprite = nullptr;
    Sprite* back = nullptr;

    std::unique_ptr<AudioSource>BGM_over;
    std::unique_ptr<AudioSource>SE_button;
};
