#ifndef MISS_IMAGE_H_
#define MISS_IMAGE_H_

#include <GSgame.h>

//HACK:���̃~�j�V�[���Ə������Ԃ�
//�X�e�[�W�~�X���o�N���X
class MissImage
{
public:
	//������
	void initialize();
	void update(float delta_time);
	void draw() const;
	//�I���������H
	bool is_end() const;

private:
	float timer_{ 0.0f };
	bool is_end_{ false };
	GSvector2 position_{ 0.0f, 0.0f };
	GSvector2 velocity_{ 0.0f, 0.0f };
};
#endif//!MISS_IMAGE_H_

