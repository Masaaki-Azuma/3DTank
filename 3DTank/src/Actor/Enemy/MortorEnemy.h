#ifndef MORTAR_ENEMY_H_
#define MORTAR_ENEMY_H_

#include "Enemy.h"

//ˆÚ“®‚Í‚¹‚¸AL”ÍˆÍ‚ğUŒ‚‚Å‚«‚é“G
class MortorEnemy : public Enemy
{
public:
	MortorEnemy(IWorld* world, const GSvector3& position);
protected:
	//ˆÚ“®
	virtual void move(float delta_time) override;
};
#endif//!MORTAR_ENEMY_H_

