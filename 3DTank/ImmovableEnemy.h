#ifndef IMMOVABLE_ENEMY_H_
#define IMMOVABLE_ENEMY_H_

#include "Enemy.h"

//�����Ȃ��G
class ImmovableEnemy : public Enemy
{
public:
	ImmovableEnemy(IWorld* world, const GSvector3& position);
private:
	//�e�𔭎�
	virtual void shoot(float delta_time) override;
};
#endif//!IMMOVABLE_ENEMY_H_

