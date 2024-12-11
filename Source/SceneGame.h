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

protected:
	DirectX::XMFLOAT3		position = { 0,0,0 };
	DirectX::XMFLOAT3		angle = { 0,0,0 };
	DirectX::XMFLOAT4X4		transform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

private:

	CameraController* cameraController = nullptr;

	Sprite* gauge = nullptr;

	Sprite* tentative_UI = nullptr;

	Clock* clock = nullptr;

	Model* desk = nullptr;

	std::unique_ptr<AudioSource>BGM_game;
};
