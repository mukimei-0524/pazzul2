#include "Scene1Select.h"
#include "SceneLoading.h"
#include "SceneGame.h"
#include "Graphics/Graphics.h"
#include "Input/Input.h"
#include "SceneManager.h"

void Scene1Select::Initialize()
{
    Graphics& graphics = Graphics::Instance();

    //stage1,2,3
    stage_1 = new Sprite("Data/Sprite/stage_1.png");
    stage_2 = new Sprite("Data/Sprite/stage_2.png");
    stage_3 = new Sprite("Data/Sprite/stage_3.png");

    //titleに戻る
   //back = new Sprite();

    // 初期設定
    Stage* stage;

}

void Scene1Select::Finalize()
{
    if (stage_1) { delete stage_1; stage_1 = nullptr; }
    if (stage_2) { delete stage_2; stage_2 = nullptr; }
    if (stage_3) { delete stage_3; stage_3 = nullptr; }
    //if (back) { delete back; back = nullptr; }
}

void Scene1Select::Update(float elapsedTime)
{
    Mouse& mouse = Input::Instance().GetMouse();

    // マウスクリックチェック
    if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
    {
        HandleClick(mouse.GetPositionX(), mouse.GetPositionY());
    }
}

void Scene1Select::Render()
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
    
    // 2Dスプライト描画
    float screenWidth = static_cast<float>(graphics.GetScreenWidth());
    float screenHeight = static_cast<float>(graphics.GetScreenHeight());
    float textureWidth1 = static_cast<float>(stage_1->GetTextureWidth());
    float textureHeight1 = static_cast<float>(stage_1->GetTextureHeight());
    // チュートリアルスプライト描画
    stage_1->Render(dc,
        screenWidth *0.25f, screenHeight *0.1f, screenWidth *0.5f, screenHeight *0.18f,
        0, 0, textureWidth1, textureHeight1,
        0, 1, 1, 1, 1);
    
  
    float textureWidth2 = static_cast<float>(stage_2->GetTextureWidth());
    float textureHeight2 = static_cast<float>(stage_2->GetTextureHeight());
    // チュートリアルスプライト描画
    stage_2->Render(dc,
        screenWidth * 0.25f, screenHeight * 0.4f, screenWidth * 0.5f, screenHeight * 0.18f,
        0, 0, textureWidth2, textureHeight2,
        0, 1, 1, 1, 1);
   
    float textureWidth3 = static_cast<float>(stage_3->GetTextureWidth());
    float textureHeight3 = static_cast<float>(stage_3->GetTextureHeight());
    // チュートリアルスプライト描画
    stage_3->Render(dc,
        screenWidth * 0.25f, screenHeight * 0.7f, screenWidth * 0.5f, screenHeight * 0.18f,
        0, 0, textureWidth3, textureHeight3,
        0, 1, 1, 1, 1);
    

    stage_1->SetPosition(screenWidth * 0.25f, screenHeight * 0.1f, screenWidth * 0.5f, screenHeight * 0.18f);
    stage_2->SetPosition(screenWidth * 0.25f, screenHeight * 0.4f, screenWidth * 0.5f, screenHeight * 0.18f);
    stage_3->SetPosition(screenWidth * 0.25f, screenHeight * 0.7f, screenWidth * 0.5f, screenHeight * 0.18f);
}

void Scene1Select::HandleClick(int x, int y)
{
    if (stage_1->HitTest(x, y))
    {
        //SE_select->Play(false);
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneFind()));
    }  

    if (stage_2->HitTest(x, y))
    {
        //SE_select->Play(false);
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneFind()));
    }

    if (stage_3->HitTest(x, y))
    {
        //SE_select->Play(false);
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneFind()));
    }
}
