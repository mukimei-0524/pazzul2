#include "Input/Input.h"

#include "SceneFind.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "SceneGame.h"

#include "ChipManager.h"
#include "mapchip.h"
#include "Chip.h"
#include "camera.h"
#include "UIManager.h"

//番号でピース設置
//int PieceIndex
//bool,,,true(あってる)
// bool ...true(見つけた)
//playerManagerで
//シーン開始時にピースを5つ取り付ける
//０～４の順番に並べる
//タッチしてタッチしてあっていたらアルファ値戻す
//もし見つけて、かつあっていたら

void SceneFind::Initialize()
{
	//player初期化
	actor = new Actor();

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
	cameraController_2 = new CameraController_2();

	//床の初期化
	ChipManager& chipManager = ChipManager::Instance();
	for (int y = 0; y <= 7; ++y)
	{
		for (int x = 0; x <= 7; ++x)
		{
			//switch文でチップの種類を切り替える
			Chip* chip = new Chip();
			chip->SetPosition(DirectX::XMFLOAT3(x * 23.0f - 23 * 7 / 2, 0, y * 23.0f - 23 * 7 / 2));
			chipManager.Register(chip);
		}
	}

	wall = new Wall();

	//UI_Memo
	UIManager& uiManager = UIManager::Instance();
	memo = new UI_Memo();
	memo->Initialize();
	uiManager.UIRegister(memo);

	//UIの時計初期化
	clock = new Clock();
	clock->Initialize();
	uiManager.UIRegister(clock);
}

void SceneFind::Finalize()
{
	//カメラコントローラー終了化
	if (cameraController_2 != nullptr)
	{
		delete cameraController_2;
		cameraController_2 = nullptr;
	}

	//player終了化
	if (actor != nullptr)
	{
		delete actor;
		actor = nullptr;
	}

	//Wall終了化
	if (wall != nullptr)
	{
		delete wall;
		wall = nullptr;
	}

	ChipManager::Instance().Clear();

	//UI終了化
	UIManager::Instance().Clear();
}

void SceneFind::Update(float elapsedTime)
{
	//時間の更新
	timer += elapsedTime;
	
	//カメラコントローラー更新処理
	DirectX::XMFLOAT3 target = { 0.0f, 0.0f, 0.0f };
	target.y += 0.5f;
	cameraController_2->SetTarget(target);
	cameraController_2->Update(elapsedTime);

	actor->Update(elapsedTime);

	wall->Update(elapsedTime);

	//Enterを押したらゲーム画面へ(のちに作業台の前に来たらへ変更)
	GamePad& gamePad = Input::Instance().GetGamePad();
	const GamePadButton anyBotton = GamePad::BTN_START;

	if (gamePad.GetButtonDown() & anyBotton)
	{
		// SceneManagerに現在のタイマーを設定してからシーンを切り替え
		SceneManager::Instance().SetTimer(timer);  // 現在のタイマーを保存
		SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame()));
	}
	//床チップ一つ分のの更新処理
	ChipManager::Instance().Update(elapsedTime);

	//UI更新処理
	UIManager::Instance().Update(elapsedTime);

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

	actor->Render(dc, shader);

	wall->Render(dc, shader);

	ChipManager::Instance().Render(dc, shader);

	shader->End(dc);

	UIManager::Instance().Render();
}
