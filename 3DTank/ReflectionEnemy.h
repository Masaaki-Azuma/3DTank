#ifndef REFLECTION_ENEMY_H_
#define REFLECTION_ENEMY_H_

#include "Enemy.h"

//•Ç‚É“–‚½‚é‚Æ”½Ë‚·‚é“G
class ReflectionEnemy : public Enemy
{
public:
	ReflectionEnemy(IWorld* world, const GSvector3& position);
private:
	//’e‚ğ”­Ë
	virtual void shoot(float delta_time) override;
	//•Ç‚ÉÕ“Ë‚Ì‹““®
	virtual void react_wall() override;
};
#endif//!REFLECTION_ENEMY_H_

