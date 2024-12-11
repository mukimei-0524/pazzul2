#include "Graphics/Graphics.h"
#include "Input/Input.h"

#include "SceneClear.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "SceneLoading.h"

void SceneClear::Initialize()
{
    //�X�v���C�g������
    sprite = new Sprite("Data/Sprite/Clear.png");
    back = new Sprite("Data/Sprite/back.png");

    BGM_clear = Audio::Instance().LoadAudioSource("Data/Audio/BGM/gameClear.wav");
    SE_button = Audio::Instance().LoadAudioSource("Data/Audio/SE/button.wav");
    BGM_clear->Play(false);
}

void SceneClear::Finalize()
{
    //�X�v���C�g�I����
    if (sprite != nullptr)
    {
        delete sprite;
        sprite = nullptr;
    } 
    if (back != nullptr)
    {
        delete back;
        back = nullptr;
    }
    BGM_clear->Stop();
}

void SceneClear::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    //�����{�^�����������烍�[�f�B���O�V�[���֐؂�ւ�

    Mouse& mouse = Input::Instance().GetMouse();

    // �}�E�X�N���b�N�`�F�b�N
    if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
    {
        SE_button->Play(false);
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTitle));
    }
}

void SceneClear::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    //��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
    FLOAT color[] = { 0.0f,0.0f,0.5f,1.0f };
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    //2D�X�v���C�g�`��
    {
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());
        //�^�C�g���X�v���C�g�`��
        sprite->Render(dc,
            0, 0, screenWidth, screenHeight,
            0, 0, textureWidth, textureHeight,
            0, 1, 1, 1, 1);

       
        float textureWidth1 = static_cast<float>(back->GetTextureWidth());
        float textureHeight1 = static_cast<float>(back->GetTextureHeight());
        back->Render(dc,
            0, 0, screenWidth * 0.2f, screenHeight * 0.1f,
            0, 0, textureWidth1, textureHeight1,
            0, 1, 1, 1, 1);

        back->SetPosition(0, 0, screenWidth * 0.2f, screenHeight * 0.1f);
        
    }
}

void SceneClear::HandleClick(int x, int y)
{
    if (back->HitTest(x, y))
    {
        //SE_select->Play(false);
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneTitle()));
    }
}
