#ifndef LEVEL_IMAGE_H_
#define LEVEL_IMAGE_H_

#include "Actor.h"

class IWorld;

//レベル情報演出を管理するクラス
class LevelImage : public Actor
{
public:
	LevelImage(IWorld* world);
	virtual void update(float delta_time) override;
	virtual void draw_gui() const override;

private:
	float timer_{ 0.0f };
};
#endif//!LEVEL_IMAGE_H_

