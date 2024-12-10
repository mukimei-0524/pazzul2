#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Character.h"
#include "Effect.h"
#include "Collision.h"
#include "PlayerManager.h"

//playerをピースとする
//プレイヤー
class Player :public Character
{
public:
	Player(const char* filename);
	~Player() override;

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//デバッグ用GUI描画
	void DrawDebugGUI();

	// レイキャスト
	bool RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit);

	void SetAlpha(float alpha) { this->alpha = alpha; }  // アルファ値を設定する
	bool IsSelected() const { return isSelected; }       // 選択状態の取得
	void SetSelected(bool selected) { isSelected = selected; }  // 選択状態を設定

private:
	Model* model = nullptr;

	//プレイヤーが選択されたかどうか
	bool isSelected = false;

	//スティック入力値から移動ベクトルを取得
	DirectX::XMFLOAT3 GetMoveVec() const;
};