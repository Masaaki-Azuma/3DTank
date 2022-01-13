#ifndef LEVEL_IMAGE_H_
#define LEVEL_IMAGE_H_

#include "Util/NumberTexture.h"

//���x����񉉏o���Ǘ�����N���X�B�~�j�V�[��
class LevelImage
{
public:
	LevelImage();
	//������
	void initialize(int level);
	void update(float delta_time);
	void draw() const;
	//�I���������H
	bool is_end() const;

private:
	float timer_{ 0.0f };
	bool is_end_{ false };
	NumberTexture number_;
	int level_{ -1 };
};
#endif//!LEVEL_IMAGE_H_

