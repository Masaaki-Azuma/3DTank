#ifndef BOUNCE_ENEMY_H_
#define BOUNCE_ENEMY_H_

#include "Enemy.h"

class BounceEnemy :
    public Enemy
{
public:
    BounceEnemy(IWorld* world, const GSvector3& position);

protected:
    virtual void move(float delta_time) override;
    virtual void generate_cannon_ball(const GSvector3& position, const GSvector3& destination) override;
};
#endif//!BOUNCE_ENEMY_H_

