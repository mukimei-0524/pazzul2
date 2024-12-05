#pragma once

#include "UI.h"
#include "UIManager.h"

class UI_Memo_Switch :public UI
{
public:
	UI_Memo_Switch() {};
	~UI_Memo_Switch()override {};

	//初期化
	void Initialize() override;

	//終了化
	void Finalize() override;

	//更新処理
	void Update(float elapsedTime) override;

	//描画処理
	void Render() override;

private:
	Sprite* Spr_Memo_Switch = nullptr;

	float Width = 200;		//横表示サイズ(幅)
	float Height = 200;		//縦表示サイズ(高さ)

	float positionX = 1050;	//表示位置
	float positionY = 10;

};