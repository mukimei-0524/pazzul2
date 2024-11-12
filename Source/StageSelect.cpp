#include "Graphics/Graphics.h"
#include "StageSelect.h"
#include "Camera.h"
#include "Input/Input.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "SceneGame.h"

void StageSelect::Initialize()
{
	Graphics& graphics = Graphics::Instance();

	//スプライト初期化



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

void StageSelect::Finalize()
{
}

void StageSelect::Update(float elapsedTime)
{
}

void StageSelect::Render()
{
}
