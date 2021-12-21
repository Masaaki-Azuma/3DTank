#ifndef PLAYER_CANNON_BALL_H_
#define PLAYER_CANNON_BALL_H_

#include "CannonBall.h"
class PlayerCannonBall :
    public CannonBall
{
public :
    PlayerCannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination);

    virtual void react(Actor& other) override;
private:
    virtual void move(float delta_time) override;
};
#endif//!PLAYER_CANNON_BALL_H_

