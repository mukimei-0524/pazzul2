#pragma once

#include "Stage.h"
#include "Player.h"
#include "CameraController.h"
#include "Scene.h"
#include "UI_Clock.h"
#include "UIManager.h"
#include <Graphics/Sprite.h>
#include "SceneFind.h"
#include "Audio/Audio.h"


// ゲームシーン
class SceneGame :public Scene
{
public:
	SceneGame() {}
	~SceneGame() override {}

	// 初期化
	void Initialize() override;

	// 終了化
	void Finalize()override;

	// 更新処理
	void Update(float elapsedTime) override;

	// 描画処理
	void Render() override;

	//クリック当たり判定
	void HandleClick(ID3D11DeviceContext* dc, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection);

	//位置取得
	const DirectX::XMFLOAT3& GetPosition()const { return position; }

	//位置設定
	void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }

	//回転取得
	const DirectX::XMFLOAT3& GetAngle()const { return angle; }

	//回転設定
	void setAngle(const DirectX::XMFLOAT3& angle) { this->angle = angle; }

	//bool IsPositionCorrect(Player* player, const DirectX::XMFLOAT3& clickPos);

protected:
	DirectX::XMFLOAT3		position = { 0,0,0 };
	DirectX::XMFLOAT3		angle = { 0,0,0 };
	DirectX::XMFLOAT4X4		transform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	std::vector<DirectX::XMFLOAT3> positions = {
	{-25.0f, 0.0f, -25.0f},
	{-15.0f, 0.0f,-30.0f},
	{0.0f, 0.0f,-25.0f},
	{18.0f, 0.0f,-20.0f},
	{38.0f, 0.0f,-20.0f}
	};
private:

	CameraController* cameraController = nullptr;

	Sprite* Memo = nullptr;
	Sprite* Memo_2 = nullptr;

	Clock* clock = nullptr;

	Model* desk = nullptr;

	std::unique_ptr<AudioSource>BGM_game;

	std::vector<Player*> pieces; // ピースを管理するリスト
	int currentPieceIndex = 0;   // 現在の正解ピースのインデックス
};
