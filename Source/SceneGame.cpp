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
	//player更新処理
	PlayerManager::Instance().Update(elapsedTime);

	//カメラコントローラー更新処理
	DirectX::XMFLOAT3 target = player->GetPosition();
	target.y += 0.5f;
	cameraController->SetTarget(target);
	cameraController->Update(elapsedTime);

	//エフェクト更新処理
	EffectManager::Instance().Update(elapsedTime);
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
	rc.alpha = 0.5f;
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
		//player->DrawDebugPrimitive();

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
void SceneGame::HandleClick(ID3D11DeviceContext* dc, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection)
{
	//ビューポート
	D3D11_VIEWPORT viewport;
	UINT numViewports = 1;
	dc->RSGetViewports(&numViewports, &viewport);

	//変換行列
	DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&view);
	DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&projection);
	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();
	
	Mouse& mouse = Input::Instance().GetMouse();
	if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
	{
		//マウスカーソル座標を取得
		DirectX::XMFLOAT3 screenPosition;
		screenPosition.x = static_cast<float>(mouse.GetPositionX());
		screenPosition.y = static_cast<float>(mouse.GetPositionY());

		DirectX::XMVECTOR ScreenPosition, WorldPosition;

		//レイの始点を計算
		screenPosition.z = 0.0f;  //ビューポートの深度を0.0に設定
		//ScreenPositionをXMVECTORに変換9								
		ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);
		//始点を2Dから3Dに変換
		WorldPosition = DirectX::XMVector3Unproject
		(ScreenPosition,
			viewport.TopLeftX,   //0.0f
			viewport.TopLeftY,   //0.0f
			viewport.Width,
			viewport.Height,
			viewport.MinDepth,   //0.0f,																																																																						
			viewport.MaxDepth,   //1.0f,
			Projection,  //DirectX::XMLoadFloat4x4(&projection),
			View,        //DirectX::XMLoadFloat4x4(&view),
			World
		);

		//ワールド空間上でのレイの始点（WorldPositionをXMFLOAT3に変換）
		DirectX::XMFLOAT3 rayStart;
		DirectX::XMStoreFloat3(&rayStart, WorldPosition);

		//レイの終点を算出
		screenPosition.z = 1.0f;//ビューポートの深度を1.0に設定
		//screenPositionをXMVECTORに変換
		ScreenPosition = DirectX::XMLoadFloat3(&screenPosition);

		//始点を2Dから3Dに変換
		WorldPosition = DirectX::XMVector3Unproject
		(ScreenPosition,
			viewport.TopLeftX,   //0.0f,
			viewport.TopLeftY,   //0.0f,
			viewport.Width,
			viewport.Height,
			viewport.MinDepth,   //0.0f,																																																																						
			viewport.MaxDepth,   //1.0f,
			Projection,  //DirectX::XMLoadFloat4x4(&projection),
			View,        //DirectX::XMLoadFloat4x4(&view),
			World
		);
		//ワールド空間上でのレイの終点（WorldPositionをXMFLOAT3に変換）
		DirectX::XMFLOAT3 rayEnd;
		DirectX::XMStoreFloat3(&rayEnd, WorldPosition);

		//レイキャスト
		HitResult hit;
		if (PlayerManager::Instance().RayCast(rayStart, rayEnd, hit))
		{
			//Player*player=

			//PlayerManager::Instance().Register(player);
		}

	}
}
