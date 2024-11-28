#include "SceneFind.h"
#include "camera.h"
#include "Input/Input.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "SceneGame.h"


void SceneFind::Initialize()
{
	Floor = new Model("Data/Model/team/MDL/Floor.mdl");

	//カメラ初期設定
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAt(
		DirectX::XMFLOAT3(0, 10, -10),
		DirectX::XMFLOAT3(0, 0, 0),
		DirectX::XMFLOAT3(0, 1, 0)
	);
	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(45),
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);

	//カメラコントローラーの初期化
	cameraController = new CameraController();
}

void SceneFind::Finalize()
{
	//カメラコントローラー終了化
	if (cameraController != nullptr)
	{
		delete cameraController;
		cameraController = nullptr;
	}
	//床モデル終了化
	if (Floor != nullptr)
	{
		delete Floor;
		Floor = nullptr;
	}
}

void SceneFind::Update(float elapsedTime)
{
	//カメラコントローラー更新処理
	DirectX::XMFLOAT3 target = { 0.0f, 0.0f, 0.0f };
	target.y += 0.5f;
	cameraController->SetTarget(target);
	cameraController->Update(elapsedTime);


	//Enterを押したらゲーム画面へ(のちに作業台の画面に来たらへ変更)
	GamePad& gamePad = Input::Instance().GetGamePad();
	const GamePadButton anyBotton = GamePad::BTN_START;

	if (gamePad.GetButtonDown() & anyBotton)
	{
		SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame()));
	}
}

void SceneFind::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// 画面クリア＆レンダーターゲット設定
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0～1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// 描画処理
	RenderContext rc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ライト方向（下方向）
	//rc.alpha = 0.5f;

	//カメラパラメーター設定
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();

	Shader* shader = graphics.GetShader();
	shader->Begin(dc, rc);

	shader->SetAlpha(1.0f);
	shader->Draw(dc, Floor);

	//プレイヤーマネージャーからプレイヤーたちを描画
	PlayerManager::Instance().Render(dc, shader);
	shader->End(dc);
}
