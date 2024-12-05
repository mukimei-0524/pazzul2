#include "UI_memo_Switch.h"
#include "Graphics/Graphics.h"

void UI_Memo_Switch::Initialize()
{
	Spr_Memo_Switch = new Sprite("Data/Sprite/UI_memo.png");
}

void UI_Memo_Switch::Finalize()
{
	if (Spr_Memo_Switch != nullptr)
	{
		delete Spr_Memo_Switch;
		Spr_Memo_Switch = nullptr;
	}
}

void UI_Memo_Switch::Update(float elapsedTime)
{
}

void UI_Memo_Switch::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	//’n}‚ðo‚·‚½‚ß‚ÌUI
	Spr_Memo_Switch->Render(dc,
		positionX, positionY,
		Width,
		Height,
		0, 0,
		static_cast<float>(Spr_Memo_Switch->GetTextureWidth()),
		static_cast<float>(Spr_Memo_Switch->GetTextureHeight()),
		0,
		1, 1, 1, 1
	);
}
