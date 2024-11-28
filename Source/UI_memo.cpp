#include "UI_memo.h"
#include "Graphics/Graphics.h"

void UI_Memo::Initialize()
{
	spr_Map = new Sprite("Data/Sprite/map_memo.png");
	spr_MapUI = new Sprite("Data/Sprte/UI_memo.png");
}

void UI_Memo::Finalize()
{
	//�X�v���C�g�I����
	if (spr_Map != nullptr)
	{
		delete spr_Map;
		spr_Map = nullptr;
	}
	if (spr_MapUI != nullptr)
	{
		delete spr_MapUI;
		spr_MapUI = nullptr;
	}
}

void UI_Memo::Update(float elapsedTime)
{
}

void UI_Memo::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();

	//�n�}
	spr_Map->Render(dc,
		positionX , positionY,
		Width,
		Height,
		0, 0,
		static_cast<float>(spr_Map->GetTextureWidth()),
		static_cast<float>(spr_Map->GetTextureHeight()),
		0,
		1, 1, 1, 1
	);

	//�n�}���o�����߂�UI
	spr_MapUI->Render(dc,
		positionX , positionY,
		Width,
		Height,
		0, 0,
		static_cast<float>(spr_MapUI->GetTextureWidth()),
		static_cast<float>(spr_MapUI->GetTextureHeight()),
		0,
		1, 1, 1, 1
	);
}
