#ifndef PREDICTION_ENEMY_H_
#define PREDICTION_ENEMY_H_

#include "Enemy.h"

//•Î·ËŒ‚‚ğ‚·‚é“GƒNƒ‰ƒX
class PredictionEnemy : public Enemy
{
public:
	PredictionEnemy(IWorld* world, const GSvector3& position);
protected:
	//ˆÚ“®
	virtual void move(float delta_time) override;
	//’e‚ğ”­Ë
	virtual void shoot(float delta_time) override;
private:
	void move_walk(float delta_time);
	void move_run(float delta_time);
	void update_timer(float delta_time);

private:
	//•ÇÕ“Ë‚Éƒ‰ƒ“ƒ_ƒ€‚É“¦‚°‰ñ‚éŠÔ
	float move_timer_;
	//ˆÚ“®ó‘Ô
	GSuint move_state_;
};
#endif//!PREDICTION_ENEMY_H_

