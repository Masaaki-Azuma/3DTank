#ifndef LEVEL_IMAGE_H_
#define LEVEL_IMAGE_H_

#include "Actor.h"

class IWorld;

//���x����񉉏o���Ǘ�����N���X�B�~�j�V�[��
class LevelImage : public Actor
{
public:
	LevelImage();
	void initialize();
	virtual void update(float delta_time) override;
	//TODO:draw_gui����draw�ɕύX
	virtual void draw_gui() const override;
	bool is_end() const;

private:
	float timer_{ 0.0f };
	bool is_end_{ false };
};
#endif//!LEVEL_IMAGE_H_

