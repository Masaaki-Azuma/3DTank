#include "LevelImage.h"
#include <GSgame.h>
#include "Assets.h"

const float HoldTime{ 90.0f }; //�Œ�`�掞��

void LevelImage::initialize()
{
	timer_ = 0.0f;
	is_end_ = false;
}

void LevelImage::update(float delta_time)
{
	timer_ = std::min(timer_ + delta_time, HoldTime);
	//����L�[�ŃN���A���o���I��������
	if (gsGetKeyTrigger(GKEY_Z) && timer_ >= HoldTime) {
		is_end_ = true;
	}
}

void LevelImage::draw() const
{
	//�`��
	static GSvector2 position_stage{ 0, 100 };
	gsDrawSprite2D(Texture_Stage, &position_stage, NULL, NULL, NULL, NULL, NULL);
}

bool LevelImage::is_end() const
{
	return is_end_;
}
