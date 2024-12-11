#include "Input/Input.h"
#include "Graphics/Graphics.h"
#include <DirectXMath.h>
#include <sstream>
#include "Camera.h"

#include "actor.h"
#include "camera.h"

Actor::Actor()
{
	model = new Model("Data/Model/team/MDL/character.mdl");

	TransitionIdleState();
}

Actor::~Actor()
{
	delete model;
}

void Actor::Update(float elapsedTime)
{
	//移動入力処理
	InputMove(elapsedTime);

	//進行ベクトル取得
	DirectX::XMFLOAT3 moveVec = GetMoveVec();

	//モデルアニメーション更新処理
	model->UpdateAnimation(elapsedTime);

	//オブジェクト行列更新
	UpdateTransform();

	//モデル行列更新
	model->UpdateTransform(transform);


	//歩行モーションとジャンプモーションが一緒のモデルをもらう？
	//一旦スペースキーで掘るモーション(デバッグ用。後で相談)
	//エンター押下でワンショットアニメーション再生(のちにマウスで選択したマスに進める処理に変更)
	GamePad& gamePad = Input::Instance().GetGamePad();
	if (gamePad.GetButtonDown() & GamePad::BTN_BACK)
	{
		TransitionJumpState();
	}
	
	//掘る
	Mouse& mouse = Input::Instance().GetMouse();
	// マウスクリックチェック
	if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
	{
		HandleClick(mouse.GetPositionX(), mouse.GetPositionY());
		TransitionMineState();
	}

	switch (state)
	{
	case State::Idle:
		UpdateIdleState(elapsedTime);
		break;
	
	case State::Mine:
		UpdateMineState(elapsedTime);
		break;
	
	case State::Jump:
		UpdateJumpState(elapsedTime);
		break;
	}
}

void Actor::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	shader->Draw(dc, model);

	// デバッグ用のテキスト描画
	//Graphics::Instance().DrawText(debugInfo, 10, 10, { 1.0f, 1.0f, 1.0f }); // 座標(10, 10)に白色で描画
}

DirectX::XMFLOAT3 Actor::GetMoveVec() const
{
	//入力情報を取得
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisLX();
	float ay = gamePad.GetAxisLY();

	//カメラ方向とスティックの入力値によって進行方向を計算する
	Camera& camera = Camera::Instance();
	const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
	const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

	DirectX::XMFLOAT3 vec;
	//カメラ右方向ベクトルをXZ単位ベクトルに変換
	float cameraRightX = cameraRight.x;
	float cameraRightZ = cameraRight.z;
	float cameraRightLength = sqrtf(cameraRightX * cameraRightX + cameraRightZ * cameraRightZ);
	if (cameraRightLength > 0.0f)
	{
		//単位ベクトル化
		cameraRightX /= cameraRightLength;
		cameraRightZ /= cameraRightLength;
	}

	//カメラ前方向ベクトルをXZ単位ベクトルに変換
	float cameraFrontX = cameraFront.x;
	float cameraFrontZ = cameraFront.z;
	float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX + cameraFrontZ * cameraFrontZ);
	if (cameraFrontLength > 0.0f)
	{
		//単位ベクトル化
		cameraFrontX /= cameraFrontLength;
		cameraFrontZ /= cameraFrontLength;
	}

	//スティックの水平入力値をカメラ右方向に反映し、
	//スティックの垂直入力値をカメラ前方向に反映し、
	//進行ベクトルを計算する
	vec.x = cameraRightX * ax + cameraFrontX * ay;
	vec.z = cameraRightZ * ax + cameraFrontZ * ay;
	//Y軸方向には移動しない
	vec.y = 0.0f;

	return vec;
}

bool Actor::InputMove(float elapsedTime)
{
	//進行ベクトル取得
	DirectX::XMFLOAT3 moveVec = GetMoveVec();

	//移動処理
	Move(elapsedTime,moveVec.x, moveVec.z, moveSpeed);

	//旋回処理
	Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);

	return moveVec.x != 0.0f || moveVec.y != 0.0f || moveVec.z != 0.0f;
}

void Actor::TransitionIdleState()
{
	state = State::Idle;
}

void Actor::UpdateIdleState(float elapsedTime)
{
	if (InputMove(elapsedTime))
	{
		TransitionJumpState();
	}
}

// 掘る
void Actor::TransitionMineState()
{
	state = State::Mine;

	model->PlayAnimation(MIne, false);
}

void Actor::UpdateMineState(float elapsedTime)
{
	if (!InputMove(elapsedTime))
	{
		TransitionIdleState();
	}
}

// ジャンプ
void Actor::TransitionJumpState()
{
	state = State::Jump;

	model->PlayAnimation(Jump, true);
}

void Actor::UpdateJumpState(float elapsedTime)
{
	if (!InputMove(elapsedTime))
	{
		TransitionIdleState();
	}
}

void Actor::HandleClick(int mouseX, int mouseY)
{
	// スクリーン座標を正規化デバイス座標に変換 (-1.0 ～ 1.0 の範囲にマッピング)
	float ndcX = (2.0f * mouseX) / Graphics::Instance().GetScreenWidth() - 1.0f;
	float ndcY = 1.0f - (2.0f * mouseY) / Graphics::Instance().GetScreenHeight();

	// カメラからビュー行列とプロジェクション行列を取得
	DirectX::XMFLOAT4X4 viewMatrixFloat4x4 = Camera::Instance().GetView();
	DirectX::XMFLOAT4X4 projectionMatrixFloat4x4 = Camera::Instance().GetProjection();

	// XMMATRIX に変換
	DirectX::XMMATRIX viewMatrix = DirectX::XMLoadFloat4x4(&viewMatrixFloat4x4);
	DirectX::XMMATRIX projectionMatrix = DirectX::XMLoadFloat4x4(&projectionMatrixFloat4x4);

	// 逆投影行列を計算
	DirectX::XMMATRIX invViewProj = DirectX::XMMatrixInverse(nullptr, viewMatrix * projectionMatrix);

	// 正規化デバイス座標をワールド座標に変換
	DirectX::XMVECTOR rayOrigin = DirectX::XMVector3TransformCoord(
		DirectX::XMVectorSet(ndcX, ndcY, 0.0f, 1.0f), invViewProj
	);

	DirectX::XMVECTOR rayDir = DirectX::XMVector3TransformNormal(
		DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), invViewProj
	);
	rayDir = DirectX::XMVector3Normalize(rayDir);

	// レイと特定の場所やオブジェクトの衝突判定
	bool hit = false;
	DirectX::XMFLOAT3 hitPosition = { 0.0f, 0.0f, 0.0f };
	if (0)
	{
		hit = true;
		hitPosition = {};
		clickCount++;
		TransitionMineState();
	}

	// デバッグ用情報更新
	DirectX::XMStoreFloat3(&debugClickPosition, rayOrigin);
	std::ostringstream oss;
	oss << "Mouse: (" << mouseX << ", " << mouseY << ")"
		<< " | Ray Origin: (" << debugClickPosition.x << ", " << debugClickPosition.y << ", " << debugClickPosition.z << ")"
		<< " | Count: " << clickCount;
	debugInfo = oss.str();
}
//配列作る
// チップクラス継承したクラス作る？enum管理？
//y軸反転させる
//生成
//8.5x8.5
//chip classで取得済みかどうかのフラグ

