#include "MissImage.h"
#include "Screen.h"
#include "Assets.h"

const float HoldTime{ 120.0f }; //最低描画時間
const GSvector2 ImageSize{ 540, 220 };
const GSvector2 Acceleration{ 0.0f, 0.8f };

void MissImage::initialize()
{
	timer_ = 0.0f;
	is_end_ = false;
	position_ = GSvector2{ Screen::Width / 2, -ImageSize.y };
	velocity_ = GSvector2{ 0.0f, 0.0f };
}

void MissImage::update(float delta_time)
{
	timer_ = std::min(timer_ + delta_time, HoldTime);
	//徐々に画像が下へ落下
	position_ += velocity_ * delta_time;
	//決定キーでミス演出を終了し次へ
	if (gsGetKeyTrigger(GKEY_Z) && timer_ >= HoldTime) {
		is_end_ = true;
	}
	if (position_.y > 340) {
		position_.y = 340;
		return;
	}
	velocity_ += Acceleration * delta_time;
}

void MissImage::draw() const
{
	const static GSvector2 center{ ImageSize / 2 };
	gsDrawSprite2D(Texture_Miss, &position_, NULL, &center, NULL, NULL, 5.0f);
}

bool MissImage::is_end() const
{
    return is_end_;
}
