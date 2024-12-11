#include "Graphics/Graphics.h"
#include "Input/Input.h"
#include "Graphics/LambertShader.h"

#include "Scene.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneClear.h"

#include "camera.h"
#include "PlayerManager.h"
#include "StageMain.h"


//2Dのやり方を調べる（グリット移動）
// パックマン参考
// 初期化
void SceneGame::Initialize()
{
#if 0
	//ステージ初期化
	//stage = new Stage();

	StageManager& stageManager = StageManager::Instance();
	StageMain* stageMain = new StageMain();

	stageManager.Register(stageMain);
	//StageMoveFloor* stageMoveFloor = new StageMoveFloor();
	//stageMoveFloor->SetStartPoint(DirectX::XMFLOAT3(0, 1, 3));
	//stageMoveFloor->SetGoalPoint(DirectX::XMFLOAT3(10, 2, 3));
	//stageMoveFloor->SetTorque(DirectX::XMFLOAT3(0, 1.0f, 0));
	//stageManager.Register(stageMoveFloor);
#endif
	
	//tentative_UI = new Sprite("Data/Sprite/tentative_UI.png");

	//机モデル初期化
	desk = new Model("Data/Model/team/MDL/desk_02.mdl");

	//プレイヤー初期化
	{
		//Rock_01
		{
			//分割数5
			Player* player = new Player("Data/Model/team/MDL/Rock_01_5-0.mdl");
			PlayerManager::Instance().Register(player);		//ピース(player)を登録

			player = new Player("Data/Model/team/MDL/Rock_01_5-1.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_5-2.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_5-3.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_5-4.mdl");
			PlayerManager::Instance().Register(player);
#if 0
			//分割数2
			player = new Player("Data/Model/team/MDL/Rock_01_2-1.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_2-2.mdl");
			PlayerManager::Instance().Register(player);

			//分割数7
			player = new Player("Data/Model/team/MDL/Rock_01_7-1.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_7-2.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_7-3.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_7-4.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_7-5.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_7-6.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_7-7.mdl");
			PlayerManager::Instance().Register(player);

			//分割数10
			player = new Player("Data/Model/team/MDL/Rock_01_10-1.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_10-2.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_10-3.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_10-4.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_10-5.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_10-6.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_10-7.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_10-8.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_10-9.mdl");
			PlayerManager::Instance().Register(player);

			player = new Player("Data/Model/team/MDL/Rock_01_10-10.mdl");
			PlayerManager::Instance().Register(player);
#endif
		}

		//Rock_02
		{
			////分割数3
			//Player* player = new Player("Data/Model/team/MDL/Rock_02_3-1.mdl");
			//PlayerManager::Instance().Register(player);

			//player = new Player("Data/Model/team/MDL/Rock_02_3-2.mdl");
			//PlayerManager::Instance().Register(player);

			//player = new Player("Data/Model/team/MDL/Rock_02_3-3.mdl");
			//PlayerManager::Instance().Register(player);

			////分割数7
			//player = new Player("Data/Model/team/MDL/Rock_02_7-1.mdl");
			//PlayerManager::Instance().Register(player);		 
			//												 
			//player = new Player("Data/Model/team/MDL/Rock_02_7-2.mdl");
			//PlayerManager::Instance().Register(player);		 
			//												 
			//player = new Player("Data/Model/team/MDL/Rock_02_7-3.mdl");
			//PlayerManager::Instance().Register(player);		 
			//												 
			//player = new Player("Data/Model/team/MDL/Rock_02_7-4.mdl");
			//PlayerManager::Instance().Register(player);		 
			//												 
			//player = new Player("Data/Model/team/MDL/Rock_02_7-5.mdl");
			//PlayerManager::Instance().Register(player);		 
			//												 
			//player = new Player("Data/Model/team/MDL/Rock_02_7-6.mdl");
			//PlayerManager::Instance().Register(player);		 
			//												 
			//player = new Player("Data/Model/team/MDL/Rock_02_7-7.mdl");
			//PlayerManager::Instance().Register(player);

			////分割数10
			//player = new Player("Data/Model/team/MDL/Rock_02_10-1.mdl");
			//PlayerManager::Instance().Register(player);

			//player = new Player("Data/Model/team/MDL/Rock_02_10-2.mdl");
			//PlayerManager::Instance().Register(player);

			//player = new Player("Data/Model/team/MDL/Rock_02_10-3.mdl");
			//PlayerManager::Instance().Register(player);

			//player = new Player("Data/Model/team/MDL/Rock_02_10-4.mdl");
			//PlayerManager::Instance().Register(player);

			//player = new Player("Data/Model/team/MDL/Rock_02_10-5.mdl");
			//PlayerManager::Instance().Register(player);

			//player = new Player("Data/Model/team/MDL/Rock_02_10-6.mdl");
			//PlayerManager::Instance().Register(player);

			//player = new Player("Data/Model/team/MDL/Rock_02_10-7.mdl");
			//PlayerManager::Instance().Register(player);

			//player = new Player("Data/Model/team/MDL/Rock_02_10-8.mdl");
			//PlayerManager::Instance().Register(player);

			//player = new Player("Data/Model/team/MDL/Rock_02_10-9.mdl");
			//PlayerManager::Instance().Register(player);

			//player = new Player("Data/Model/team/MDL/Rock_02_10-10.mdl");
			//PlayerManager::Instance().Register(player);
		}

		//Rock_03
		{
		//	//分割数4
		//	Player* player = new Player("Data/Model/team/MDL/Rock_03_4-1.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_4-2.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_4-3.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_4-4.mdl");
		//	PlayerManager::Instance().Register(player);

		//	//分割数7
		//	player = new Player("Data/Model/team/MDL/Rock_03_7-1.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_7-2.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_7-3.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_7-4.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_7-5.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_7-6.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_7-7.mdl");
		//	PlayerManager::Instance().Register(player);

		//	//分割数10
		//	player = new Player("Data/Model/team/MDL/Rock_03_10-1.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_10-2.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_10-3.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_10-4.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_10-5.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_10-6.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_10-7.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_10-8.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_10-9.mdl");
		//	PlayerManager::Instance().Register(player);

		//	player = new Player("Data/Model/team/MDL/Rock_03_10-10.mdl");
		//	PlayerManager::Instance().Register(player);
		}
	}

	for (int i = 0; i < 5; ++i)
	{
		Player* player = new Player(("Data/Model/team/MDL/Rock_01_5-" + std::to_string(i) + ".mdl").c_str());
		// ピースを順番に配置
		player->SetPosition({ i * 10.0f, 0.0f, -20.0f });
		PlayerManager::Instance().Register(player);
		pieces.push_back(player); // ピースリストに追加
	}

	//カメラ初期設定
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAt(
		DirectX::XMFLOAT3(0, 53, -53),
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

	//UIの時計初期化
	int initialTimer = SceneManager::Instance().GetTimer();
	UIManager& uiManager = UIManager::Instance();
	clock = new Clock();
	clock->Initialize();
	clock->SetTimer(initialTimer);
	uiManager.UIRegister(clock);
	
	BGM_game = Audio::Instance().LoadAudioSource("Data/Audio/BGM/game.wav");
	BGM_game->Play(false);


}

// 終了化
void SceneGame::Finalize()
{
	//StageManager::Instance().Clear();

	//プレイヤーマネージャーからプレーヤーたちを終了化
	PlayerManager::Instance().Clear();

	//カメラコントローラー終了化
	if (cameraController != nullptr)
	{
		delete cameraController;
		cameraController = nullptr;
	}

	//ピースの下の四角終了化
	//if (tentative_UI != nullptr)
	//{
		//delete tentative_UI;
		//tentative_UI = nullptr;
	//}

	//UI終了化
	UIManager::Instance().Clear();

	//机終了化
	if (desk != nullptr)
	{
		delete desk;
		desk = nullptr;
	}
	BGM_game->Stop();
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	//StageManager::Instance().Update(elapsedTime);

	//UI更新処理
	UIManager::Instance().Update(elapsedTime);

	//player更新処理
	PlayerManager::Instance().Update(elapsedTime);

	//時間の再開
	float saveTime = SceneManager::Instance().GetTimer();

	//saveTimeを元に何か処理


	//時間を進める
	SceneManager::Instance().SetTimer(saveTime + elapsedTime);

	//カメラコントローラー更新処理
	DirectX::XMFLOAT3 target = {0.0f, 0.0f, 0.0f};
	target.y += 0.5f;
	cameraController->SetTarget(target);
	cameraController->Update(elapsedTime);

	GamePad& gamePad = Input::Instance().GetGamePad();
	const GamePadButton anyBotton = GamePad::BTN_START;
	if (gamePad.GetButtonDown() & anyBotton)
	{
		// SceneManagerに現在のタイマーを設定してからシーンを切り替え
		//SceneManager::Instance().SetTimer(timer);  // 現在のタイマーを保存
		SceneManager::Instance().ChangeScene(new SceneClear);
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
	FLOAT color[] = { 0.16f, 0.07f, 0.07f, 1.0f };	// RGBA(0.0～1.0)
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

	//仮のUI
	float screenWidth = static_cast<float>(graphics.GetScreenWidth());
	float screenHeight = static_cast<float>(graphics.GetScreenHeight());
	//float textureWidth = static_cast<float>(tentative_UI->GetTextureWidth());
	//float textureHeight = static_cast<float>(tentative_UI->GetTextureHeight());
	//float positionX = screenWidth - textureWidth;
	//float positionY = screenHeight - textureHeight;

	HandleClick(dc, rc.view, rc.projection);

	// 3Dモデル描画
	{
		Shader* shader = graphics.GetShader();
		shader->Begin(dc, rc);
		shader->SetAlpha(1.0f);
		shader->Draw(dc, desk);
		
		//プレイヤーマネージャーからプレイヤーたちを描画
		PlayerManager::Instance().Render(dc, shader);
		shader->End(dc);
	}

	//2Dスプライト描画
	{
		UIManager::Instance().Render();
	}

	//後で変更
	//tentative_UI->Render(dc,
	//	0, 400, 1280, 760,
	//	0, 0, textureWidth, textureHeight,
	//	0,
	//	1, 1, 1, 1
	//);
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
			hit.hitPlayer->SetAlpha(1.0f);
			Player* player = nullptr;
		}
	}
}
