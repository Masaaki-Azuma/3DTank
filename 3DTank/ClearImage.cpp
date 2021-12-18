#include "ClearImage.h"
#include "IWorld.h"
#include "Assets.h"

const float HoldTime{ 60.0f };
ClearImage::ClearImage()
{
	name_ = "ClearImage";
	tag_ = "TextImage";
}

void ClearImage::initialize()
{
	timer_ = 0.0f;
	is_end_ = false;
}

void ClearImage::update(float delta_time)
{
	timer_ = std::min(timer_ + delta_time, HoldTime);
	//決定キーでクリア演出を終了し次へ
	if (gsGetKeyTrigger(GKEY_Z) && timer_ >= HoldTime) {
		is_end_ = true;;
	}
}

void ClearImage::draw_gui() const
{
	//描画
	static GSvector2 position_stage{ 0, 100 };
	gsDrawSprite2D(Texture_Clear, &position_stage, NULL, NULL, NULL, NULL, NULL);
}

bool ClearImage::is_end() const
{
	return is_end_;
}
