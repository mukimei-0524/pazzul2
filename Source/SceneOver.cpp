#include "Graphics/Graphics.h"
#include "SceneOver.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "Input/Input.h"
#include "SceneLoading.h"

// test

//初期化
void SceneOver::Initialize()
{
    //スプライト初期化
    sprite = new Sprite("Data/Sprite/Over.png");
    back = new Sprite("Data/Sprite/back.png");

    BGM_over = Audio::Instance().LoadAudioSource("Data/Audio/BGM/gameOver.wav");
    SE_button = Audio::Instance().LoadAudioSource("Data/Audio/SE/button.wav");
    BGM_over->Play(false);
}

//終了化
void SceneOver::Finalize()
{
    //スプライト終了化
    if (sprite != nullptr) {
        delete sprite;
        sprite = nullptr;
    } 
    if (back != nullptr) {
        delete back;
        back = nullptr;
    }
    BGM_over->Stop();
}

//更新処理
void SceneOver::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    //マウスクリックしたらローディングシーンへ切り替え
    Mouse& mouse = Input::Instance().GetMouse();

    // マウスクリックチェック
    if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
    {
        SE_button->Play(false);
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTitle));
    }
}

//描画処理
void SceneOver::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    //画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f,0.0f,0.5f,1.0f };
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    //2Dスプライト描画
    {
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());
        //タイトルスプライト描画
        sprite->Render(dc,
            0, 0, screenWidth, screenHeight,
            0, 0, textureWidth, textureHeight,
            0, 1, 1, 1, 1);

        if (back)
        {
            float textureWidth1 = static_cast<float>(back->GetTextureWidth());
            float textureHeight1 = static_cast<float>(back->GetTextureHeight());
            back->Render(dc,
                0, 0, screenWidth * 0.2f, screenHeight * 0.1f,
                0, 0, textureWidth1, textureHeight1,
                0, 1, 1, 1, 1);

            back->SetPosition(0, 0, screenWidth * 0.2f, screenHeight * 0.1f);
        }
    }
}

void SceneOver::HandleClick(int x, int y)
{
    if (back->HitTest(x, y))
    {
        //SE_select->Play(false);
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTitle()));
    }
}
