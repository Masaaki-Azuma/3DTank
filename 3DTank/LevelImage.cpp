#include "LevelImage.h"
#include <GSgame.h>
#include "Screen.h"
#include "Assets.h"

const float HoldTime{ 60.0f }; //�Œ�`�掞��
const GSvector2 ImageSize{ 840,220 };


LevelImage::LevelImage():
	number_{Texture_Number, 68, 98}
{
}

void LevelImage::initialize(int level)
{
	timer_ = 0.0f;
	is_end_ = false;
	level_ = level;
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
	const static GSvector2 position_stage{ Screen::Width / 2, 340 };
	const static GSvector2 center{ ImageSize / 2 };
	gsDrawSprite2D(Texture_Stage, &position_stage, NULL, &center, NULL, NULL, NULL);
	//���݂̃��x����\��
	number_.draw(GSvector2{ 1100, 290 }, level_ + 1); //�\�����x���͓������x�����1�傫��
}

bool LevelImage::is_end() const
{
	return is_end_;
}
