#include "ClearImage.h"
#include "Assets.h"
#include "Sound.h"

const float HoldTime{ 120.0f };
const float ScaleMaxTime{ HoldTime * 2 / 3 };
const float SqScaleMaxTime{ ScaleMaxTime * ScaleMaxTime };
const GSvector2 ImageSize{ 1080,320 };
const GSvector2 ScaleVelocity{ GSvector2::one() * 0.02f };

void ClearImage::initialize()
{
	timer_ = 0.0f;
	is_end_ = false;
	image_scale_ = GSvector2::zero();
	//クリア音声を再生
	gsPlaySE(Se_ClearStage);
}

void ClearImage::update(float delta_time)
{
	timer_ = std::min(timer_ + delta_time, HoldTime);
	image_scale_ = std::min(image_scale_ + ScaleVelocity * delta_time, GSvector2::one());
	image_scale_ = ((timer_ - ScaleMaxTime) * (timer_ - ScaleMaxTime) / -SqScaleMaxTime + 1.0f) * GSvector2::one();
	//決定キーでクリア演出を終了し次へ
	if ((gsGetKeyTrigger(GKEY_Z) || gsXBoxPadButtonTrigger(0, GS_XBOX_PAD_A))
		&& timer_ >= HoldTime) {
		is_end_ = true;;
	}
}

void ClearImage::draw() const
{
	//描画
	const static GSvector2 position_clear{ 420 + ImageSize.x / 2, 210 + ImageSize.y / 2 };
	const static GSvector2 center{ ImageSize / 2 };
	gsDrawSprite2D(Texture_Clear, &position_clear, NULL, &center, NULL, &image_scale_, NULL);
}

bool ClearImage::is_end() const
{
	return is_end_;
}
