#include "LevelImage.h"
#include "IWorld.h"
#include "Assets.h"

const float HoldTime{ 90.0f }; //�Œ�`�掞��

LevelImage::LevelImage(IWorld* world)
{
	world_ = world;
	name_ = "LevelImage";
	tag_ = "TextImage";
}

void LevelImage::update(float delta_time)
{
	timer_ = std::min(timer_ + delta_time, HoldTime);
	//����L�[�ŃN���A���o���I��������
	if (gsGetKeyTrigger(GKEY_Z) && timer_ >= HoldTime) {
		world_->change_to_battle();
		die();
	}
}

void LevelImage::draw_gui() const
{
	//�`��
	static GSvector2 position_stage{ 0, 100 };
	gsDrawSprite2D(Texture_Stage, &position_stage, NULL, NULL, NULL, NULL, NULL);
}
