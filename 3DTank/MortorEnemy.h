#ifndef MORTAR_ENEMY_H_
#define MORTAR_ENEMY_H_

#include "Enemy.h"

//�ړ��͂����A�L�͈͂��U���ł���G
class MortorEnemy : public Enemy
{
public:
	MortorEnemy(IWorld* world, const GSvector3& position);
protected:
	//�ړ�
	virtual void move(float delta_time) override;
};
#endif//!MORTAR_ENEMY_H_

