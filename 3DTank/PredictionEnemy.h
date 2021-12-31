#ifndef PREDICTION_ENEMY_H_
#define PREDICTION_ENEMY_H_

#include "Enemy.h"

//�΍��ˌ�������G�N���X
class PredictionEnemy : public Enemy
{
public:
	PredictionEnemy(IWorld* world, const GSvector3& position);

	//�ړ�
	virtual void move(float delta_time) override;
	//�e�𔭎�
	virtual void shoot(float delta_time) override;

};
#endif//!PREDICTION_ENEMY_H_

