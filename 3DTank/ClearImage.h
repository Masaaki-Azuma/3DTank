#ifndef CLEAR_IAMGE_H_
#define CLEAR_IAMGE_H_

#include "Actor.h"

class IWorld;

//�N���A���o���Ǘ�����N���X
class ClearImage : public Actor
{
public:
	ClearImage(IWorld* world);
	virtual void update(float delta_time) override;
	virtual void draw_gui() const override;

private:
	float timer_{ 0.0f };
};

#endif//!CLEAR_IAMGE_H_

