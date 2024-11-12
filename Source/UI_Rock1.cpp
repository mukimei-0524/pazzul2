#include "UI_Rock1.h"

void UI_Rock1::Initialize()
{
}

void UI_Rock1::Finalize()
{
	//objs[5] 終了化
	for (Object& obj : objs)
		if (obj.spr_obj != nullptr)
		{
			delete obj.spr_obj;
			obj.spr_obj = nullptr;
		}
}

void UI_Rock1::Update(float elapsedTime)
{
	for (Object& obj : objs)
	{
		// 縮小速度の計算
		obj.scale_velocity.x += minCoefficient * elapsedTime * 100.0f;
		obj.scale_velocity.y += minCoefficient * elapsedTime * 100.0f;

		// 縮小処理
		obj.scale.x += obj.scale_velocity.x * elapsedTime;
		obj.scale.y += obj.scale_velocity.y * elapsedTime;

		// ボタンを押されていなかったら最小値を 1.0 にしておく
		if (obj.isPlay == false)
		{
			minScaling = 1.0f;
		}
		else
		{
			minScaling = 0.0f;
		}

		if (obj.scale.y < minScaling ||
			obj.scale.x < minScaling)
		{
			obj.scale.y = minScaling;
			obj.scale.x = minScaling;
			if (obj.isPlay)
			{
				obj.exist = false;
			}
		}
	}

}

void UI_Rock1::Render()
{
}
