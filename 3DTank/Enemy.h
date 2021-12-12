#ifndef ENEMY_H_
#define ENEMY_H_

#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy(IWorld* world, const GSvector3& position);

	void update(float delta_time) override;
	void draw() const override;
private:
	void move(float delta_time);
	void free_fall(float delta_time);
	void shoot(float delta_time);
	void collide_field();

private:
	float shot_timer_{ 0.0f };
};
#endif//!ENEMY_H_

