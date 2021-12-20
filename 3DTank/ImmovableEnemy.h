#ifndef IMMOVABLE_ENEMY_H_
#define IMMOVABLE_ENEMY_H_

#include "Enemy.h"

//“®‚©‚È‚¢“G
class ImmovableEnemy : public Enemy
{
public:
	ImmovableEnemy(IWorld* world, const GSvector3& position);
};
#endif//!IMMOVABLE_ENEMY_H_

