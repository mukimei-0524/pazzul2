#include "Graphics/Graphics.h"
#include "SceneSelect.h"
#include "Scene1Select.h"
#include "Scene2Select.h"
#include "Scene3Select.h"
#include "SceneTitle.h"
#include "Camera.h"
#include "Input/Input.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "SceneGame.h"

// 初期化
void SceneSelect::Initialize()
{
	Graphics& graphics = Graphics::Instance();

    // 注意書き初期化
    tutorial = new Sprite("Data/Sprite/tutorial.png");

    //staeg
    stage1 = new Sprite("Data/Sprite/stage1.png");
    stage2 = new Sprite("Data/Sprite/stage2.png");
    stage3 = new Sprite("Data/Sprite/stage3.png");
    
    // startボタン
    start = new Sprite("Data/Sprite/start.png");

    // 方向のスプライト初期化
    right = new Sprite("Data/Sprite/migi.png");
    left = new Sprite("Data/Sprite/hidari.png");

    //titleに戻る
    back = new Sprite("Data/Sprite/back.png");

    // 初期設定
    stage = Tutorial;
    currentModel = nullptr;

    //カメラ初期化
    Camera& camera = Camera::Instance();
    camera.SetLookAt(
        DirectX::XMFLOAT3(0, 1, -10),
        DirectX::XMFLOAT3(0, 1, 0),
        DirectX::XMFLOAT3(0, 1, 0)
    );
    camera.SetPerspectiveFov(
        DirectX::XMConvertToRadians(45),
        graphics.GetScreenWidth() / graphics.GetScreenHeight(),
        0.1f,
        1000.0f
    );
    scale.x = scale.y = scale.z = 0.03f;

    //オーディオ初期化
}

// 終了化
void SceneSelect::Finalize()
{
    if (tutorial) { delete tutorial; tutorial = nullptr; }
    if (stage1)   { delete stage1; stage1 = nullptr; }
    if (stage2)   { delete stage2; stage2 = nullptr; }
    if (stage3)   { delete stage3; stage3 = nullptr; }
    if (start)    { delete start; start = nullptr; }

    if (right)    { delete right; right = nullptr; }
    if (left)     { delete left; left = nullptr; }

    if (back) { delete back; back = nullptr; }
}

// 更新処理
void SceneSelect::Update(float elapsedTime)
{
    Mouse& mouse = Input::Instance().GetMouse();

    // マウスクリックチェック
    if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
    {
        HandleClick(mouse.GetPositionX(), mouse.GetPositionY());
    }
}

// 描画処理
void SceneSelect::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // 画面クリア＆レンダーターゲット設定
    //FLOAT color[] = { 0.3f, 1.0f, 0.7f, 1.0f }; // RGBA(0.0～1.0)
    FLOAT color[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // RGBA(0.0～1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    if (stage == Tutorial)
    {
        // 2Dスプライト描画
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(tutorial->GetTextureWidth());
        float textureHeight = static_cast<float>(tutorial->GetTextureHeight());

        // チュートリアルスプライト描画
        tutorial->Render(dc,
            screenWidth * 0.25f, screenHeight * 0.25f, screenWidth * 0.5f, screenHeight * 0.5f,
            0, 0, textureWidth, textureHeight,
            0, 1, 1, 1, 1);

        if (back)
        {
            float textureWidth1 = static_cast<float>(back->GetTextureWidth());
            float textureHeight1 = static_cast<float>(back->GetTextureHeight());
            back->Render(dc,
                0, 0, screenWidth * 0.2f, screenHeight * 0.1f,
                0, 0, textureWidth, textureHeight,
                0, 1, 1, 1, 1);

            back->SetPosition(0, 0, screenWidth * 0.2f, screenHeight * 0.1f);
        }

        // Startスプライト描画
        if (start)
        {
            float startWidth = static_cast<float>(start->GetTextureWidth());
            float startHeight = static_cast<float>(start->GetTextureHeight());
            float screenWidth = static_cast<float>(graphics.GetScreenWidth());
            float screenHeight = static_cast<float>(graphics.GetScreenHeight());

            float startX = screenWidth * 0.43f - 30;
            float startY = screenHeight * 0.8f;
            float startRenderWidth = startWidth * 0.1f + 100;
            float startRenderHeight = startHeight * 0.1f + 20;

            start->Render(dc,
                startX, startY, startRenderWidth, startRenderHeight,
                0, 0, startWidth, startHeight,
                0, 1, 1, 1, 1);

            start->SetPosition(startX, startY, startRenderWidth, startRenderHeight);
        }
    }
    else if (stage == Stage1)
    {
        // 2Dスプライト描画
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(tutorial->GetTextureWidth());
        float textureHeight = static_cast<float>(tutorial->GetTextureHeight());

        // タイトルスプライト描画
        stage1->Render(dc,
            0, 0, screenWidth, screenHeight,
            0, 0, textureWidth, textureHeight,
            0, 1, 1, 1, 1);

        if (back)
        {
            float textureWidth1 = static_cast<float>(back->GetTextureWidth());
            float textureHeight1 = static_cast<float>(back->GetTextureHeight());
            back->Render(dc,
                0, 0, screenWidth * 0.2f, screenHeight * 0.1f,
                0, 0, textureWidth, textureHeight,
                0, 1, 1, 1, 1);

            back->SetPosition(0, 0, screenWidth * 0.2f, screenHeight * 0.1f);
        }

        // Startスプライト描画
        if (start)
        {
            float startWidth = static_cast<float>(start->GetTextureWidth());
            float startHeight = static_cast<float>(start->GetTextureHeight());
            float screenWidth = static_cast<float>(graphics.GetScreenWidth());
            float screenHeight = static_cast<float>(graphics.GetScreenHeight());

            float startX = screenWidth * 0.43f - 30;
            float startY = screenHeight * 0.8f;
            float startRenderWidth = startWidth * 0.1f + 100;
            float startRenderHeight = startHeight * 0.1f + 20;

            start->Render(dc,
                startX, startY, startRenderWidth, startRenderHeight,
                0, 0, startWidth, startHeight,
                0, 1, 1, 1, 1);

            start->SetPosition(startX, startY, startRenderWidth, startRenderHeight);
        }
    }
    else if (stage == Stage2)
    {
        // 2Dスプライト描画
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(tutorial->GetTextureWidth());
        float textureHeight = static_cast<float>(tutorial->GetTextureHeight());

        // タイトルスプライト描画
        stage2->Render(dc,
            0, 0, screenWidth, screenHeight,
            0, 0, textureWidth, textureHeight,
            0, 1, 1, 1, 1);

        if (back)
        {
            float textureWidth1 = static_cast<float>(back->GetTextureWidth());
            float textureHeight1 = static_cast<float>(back->GetTextureHeight());
            back->Render(dc,
                0, 0, screenWidth * 0.2f, screenHeight * 0.1f,
                0, 0, textureWidth, textureHeight,
                0, 1, 1, 1, 1);

            back->SetPosition(0, 0, screenWidth * 0.2f, screenHeight * 0.1f);
        }

        // Startスプライト描画
        if (start)
        {
            float startWidth = static_cast<float>(start->GetTextureWidth());
            float startHeight = static_cast<float>(start->GetTextureHeight());
            float screenWidth = static_cast<float>(graphics.GetScreenWidth());
            float screenHeight = static_cast<float>(graphics.GetScreenHeight());

            float startX = screenWidth * 0.43f - 30;
            float startY = screenHeight * 0.8f;
            float startRenderWidth = startWidth * 0.1f + 100;
            float startRenderHeight = startHeight * 0.1f + 20;

            start->Render(dc,
                startX, startY, startRenderWidth, startRenderHeight,
                0, 0, startWidth, startHeight,
                0, 1, 1, 1, 1);

            start->SetPosition(startX, startY, startRenderWidth, startRenderHeight);
        }
    } 
    else if (stage == Stage3)
    {
        // 2Dスプライト描画
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(tutorial->GetTextureWidth());
        float textureHeight = static_cast<float>(tutorial->GetTextureHeight());

        // タイトルスプライト描画
        stage3->Render(dc,
            0, 0, screenWidth, screenHeight,
            0, 0, textureWidth, textureHeight,
            0, 1, 1, 1, 1);

        if (back)
        {
            float textureWidth1 = static_cast<float>(back->GetTextureWidth());
            float textureHeight1 = static_cast<float>(back->GetTextureHeight());
            back->Render(dc,
                0, 0, screenWidth * 0.2f, screenHeight * 0.1f,
                0, 0, textureWidth, textureHeight,
                0, 1, 1, 1, 1);

            back->SetPosition(0, 0, screenWidth * 0.2f, screenHeight * 0.1f);
        }

        // Startスプライト描画
        if (start)
        {
            float startWidth = static_cast<float>(start->GetTextureWidth());
            float startHeight = static_cast<float>(start->GetTextureHeight());
            float screenWidth = static_cast<float>(graphics.GetScreenWidth());
            float screenHeight = static_cast<float>(graphics.GetScreenHeight());

            float startX = screenWidth * 0.43f - 30;
            float startY = screenHeight * 0.8f;
            float startRenderWidth = startWidth * 0.1f + 100;
            float startRenderHeight = startHeight * 0.1f + 20;

            start->Render(dc,
                startX, startY, startRenderWidth, startRenderHeight,
                0, 0, startWidth, startHeight,
                0, 1, 1, 1, 1);

            start->SetPosition(startX, startY, startRenderWidth, startRenderHeight);
        }
    }

    // 四角のスプライト描画
    float buttonWidth = 50.0f;
    float buttonHeight = 50.0f;

    float screenWidth = static_cast<float>(graphics.GetScreenWidth());
    float screenHeight = static_cast<float>(graphics.GetScreenHeight());

    // 右の四角
    float rightButtonX = screenWidth - buttonWidth - 120.0f; // 画面右端から20ピクセル内側に配置
    float rightButtonY = screenHeight - buttonHeight - 320.0f; // 画面下端から20ピクセル上に配置
    // 左の四角
    float leftButtonX = screenWidth - buttonWidth -1100.0f; // 画面左端から20ピクセル内側に配置
    float leftButtonY = screenHeight - buttonHeight - 320.0f; // 画面下端から20ピクセル上に配置

    right->Render(dc,
        rightButtonX, rightButtonY, buttonWidth, buttonHeight,
        0, 0, 512, 512,
        0, 1, 1, 1, 1);
    
    left->Render(dc,
        leftButtonX, leftButtonY, buttonWidth, buttonHeight,
        0, 0, 512, 512,
        0, 1, 1, 1, 1);

    // クリック判定の位置とサイズを更新
    rightRect = { static_cast<LONG>(rightButtonX), static_cast<LONG>(rightButtonY), static_cast<LONG>(rightButtonX + buttonWidth), static_cast<LONG>(rightButtonY + buttonHeight) };
    leftRect = { static_cast<LONG>(leftButtonX), static_cast<LONG>(leftButtonY), static_cast<LONG>(leftButtonX + buttonWidth), static_cast<LONG>(leftButtonY + buttonHeight) };
}

// クリック判定
void SceneSelect::HandleClick(int x, int y)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    const GamePadButton rightBotton = GamePad::BTN_RIGHT;
    const GamePadButton leftBotton = GamePad::BTN_LEFT;

    if (PtInRect(&rightRect, { x, y })|| gamePad.GetButtonDown() & rightBotton)
    {
        switch (stage)
        {
        case Tutorial:
            stage = Stage1;
            break;

        case Stage1:
            stage = Stage2;
            break;

        case Stage2:
            stage = Stage3;
            break;

        case Stage3:
            stage = Tutorial;
            break;
        }
    }
    else if (PtInRect(&leftRect, { x, y })|| gamePad.GetButtonDown() & leftBotton)
    {
        switch (stage)
        {
        case Tutorial:
            stage = Stage3;
            break;

        case Stage1:
            stage  = Tutorial;
            break;

        case Stage2:
            stage = Stage1;
            break;

        case Stage3:
            stage = Stage2;
            break;
        }
    }
    // 新しいコード追加: Startスプライトのクリック判定
    if (stage == Tutorial)
    {
        if (start->HitTest(x, y))
        {
            //SE_select->Play(false);
            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneFind()));
        }
        if (back->HitTest(x, y))
        {
            //SE_select->Play(false);
            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTitle()));
        }
    }
    else if (stage == Stage1)
    {
        if (start->HitTest(x, y))
        {
            //SE_select->Play(false);
            SceneManager::Instance().ChangeScene(new SceneLoading(new Scene1Select())); // SceneGame2が完成したら有効化
        }
        if (back->HitTest(x, y))
        {
            //SE_select->Play(false);
            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTitle()));
        }
    }
    else if (stage == Stage2)
    {
        if (start->HitTest(x, y))
        {
            //SE_select->Play(false);
            SceneManager::Instance().ChangeScene(new SceneLoading(new Scene2Select())); // SceneGame2が完成したら有効化
        }
        if (back->HitTest(x, y))
        {
            //SE_select->Play(false);
            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTitle()));
        }
    }
    else if (stage == Stage3)
    {
        if (start->HitTest(x, y))
        {
            //SE_select->Play(false);
            SceneManager::Instance().ChangeScene(new SceneLoading(new Scene3Select())); // SceneGame2が完成したら有効化
        }
        if (back->HitTest(x, y))
        {
            //SE_select->Play(false);
            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTitle()));
        }
    }
}
