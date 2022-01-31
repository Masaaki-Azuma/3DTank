#ifndef BOUNCE_CANNON_BALL_H
#define BOUNCE_CANNON_BALL_H

#include "CannonBall.h"

class BounceCannonBall : public CannonBall
{
public:
	BounceCannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination);

	virtual void react(Actor& other) override;
private:
	virtual void move(float delta_time) override;
	virtual void collide_field() override;

private:
	int bounce_count{ 0 };
};
#endif//!BOUNCE_CANNON_BALL_H

