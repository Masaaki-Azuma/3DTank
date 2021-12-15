#include "ClearImage.h"
#include "IWorld.h"
#include "Assets.h"

const float HoldTime{ 60.0f };
ClearImage::ClearImage(IWorld* world)
{
  	world_ = world;
	name_ = "ClearImage";
	tag_ = "TextImage";
}

void ClearImage::update(float delta_time)
{
	timer_ = std::min(timer_ + delta_time, HoldTime);
	//����L�[�ŃN���A���o���I��������
	if (gsGetKeyTrigger(GKEY_Z) && timer_ >= HoldTime) {
		world_->change_to_level_end();
		die();
	}
}

void ClearImage::draw_gui() const
{
	//�`��
	static GSvector2 position_stage{ 0, 100 };
	gsDrawSprite2D(Texture_Clear, &position_stage, NULL, NULL, NULL, NULL, NULL);
}
