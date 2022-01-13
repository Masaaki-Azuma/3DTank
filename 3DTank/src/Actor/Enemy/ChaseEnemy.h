#ifndef CHASE_ENEMY_H_
#define CHASE_ENEMY_H_

#include "Enemy.h"

class ChaseEnemy : public Enemy
{
public:
	ChaseEnemy(IWorld* world, const GSvector3& position);
protected:
	virtual void move(float delta_time) override;
};
#endif//!CHASE_ENEMY_H_

