#include "Graphics/Graphics.h"
#include "SceneGame.h"
#include "camera.h"
#include "EffectManager.h"
#include "EffectManager.h"
#include "Input/Input.h"
#include "Scene.h"
#include "StageManager.h"
#include "StageMain.h"
//#include "StageMoveFloor.h"

// 初期化
void SceneGame::Initialize()
{
	//ステージ初期化
	//stage = new Stage();

	//StageManager& stageManager = StageManager::Instance();
	//StageMain* stageMain = new StageMain();
	//stageManager.Register(stageMain);
#if 0
	StageMoveFloor* stageMoveFloor = new StageMoveFloor();
	stageMoveFloor->SetStartPoint(DirectX::XMFLOAT3(0, 1, 3));
	stageMoveFloor->SetGoalPoint(DirectX::XMFLOAT3(10, 2, 3));
	stageMoveFloor->SetTorque(DirectX::XMFLOAT3(0, 1.0f, 0));
	stageManager.Register(stageMoveFloor);
#endif
	//プレイヤー初期化
	player = new Player();

	//ゲージスプライト
	gauge = new Sprite();

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

// 終了化
void SceneGame::Finalize()
{
	//StageManager::Instance().Clear();

	//プレイヤー終了化
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}

	//カメラコントローラー終了化
	if (cameraController != nullptr)
	{
		delete cameraController;
		cameraController = nullptr;
	}

	//ゲージスプライト終了化
	if (gauge != nullptr)
	{
		delete gauge;
		gauge = nullptr;
	}
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	//ステージ更新処理
	//StageManager::Instance().Update(elapsedTime);


	//プレイヤー更新処理
	player->Update(elapsedTime);

	//カメラコントローラー更新処理
	DirectX::XMFLOAT3 target = player->GetPosition();
	target.y += 0.5f;
	cameraController->SetTarget(target);
	cameraController->Update(elapsedTime);

	//エフェクト更新処理
	EffectManager::Instance().Update(elapsedTime);

	Mouse& mouse = Input::Instance().GetMouse();

	// マウスクリックチェック
	if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
	{
		HandleClick(mouse.GetPositionX(), mouse.GetPositionY());
	}

}

// 描画処理
void SceneGame::Render()
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

	//カメラパラメーター設定
	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();
	// 3Dモデル描画
	{
		Shader* shader = graphics.GetShader();
		shader->Begin(dc, rc);
		
		//ステージ描画
		//StageManager::Instance().Render(dc, shader);

		//プレイヤー描画
		player->Render(dc, shader);
		
		shader->End(dc);
	}

	//3Dエフェクト描画
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}

	// 3Dデバッグ描画
	{
		//プレイヤーデバッグプリミティブ描画
		player->DrawDebugPrimitive();

		// ラインレンダラ描画実行
		graphics.GetLineRenderer()->Render(dc, rc.view, rc.projection);

		// デバッグレンダラ描画実行
		graphics.GetDebugRenderer()->Render(dc, rc.view, rc.projection);

	}

	// 2DデバッグGUI描画
	{
		//playerデバック描画
		player->DrawDebugGUI();
	}
}

//クリック処理
void SceneGame::HandleClick(int x, int y)
{

}
