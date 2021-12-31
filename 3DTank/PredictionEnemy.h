#ifndef PREDICTION_ENEMY_H_
#define PREDICTION_ENEMY_H_

#include "Enemy.h"

//•Î·ËŒ‚‚ğ‚·‚é“GƒNƒ‰ƒX
class PredictionEnemy : public Enemy
{
public:
	PredictionEnemy(IWorld* world, const GSvector3& position);

	//ˆÚ“®
	virtual void move(float delta_time) override;
	//’e‚ğ”­Ë
	virtual void shoot(float delta_time) override;

};
#endif//!PREDICTION_ENEMY_H_

