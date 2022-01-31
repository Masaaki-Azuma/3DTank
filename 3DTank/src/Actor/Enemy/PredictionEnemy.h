#ifndef PREDICTION_ENEMY_H_
#define PREDICTION_ENEMY_H_

#include "Enemy.h"

//�΍��ˌ�������G�N���X
class PredictionEnemy : public Enemy
{
public:
	PredictionEnemy(IWorld* world, const GSvector3& position);
protected:
	//�ړ�
	virtual void move(float delta_time) override;
	//�e�𔭎�
	virtual void shoot(float delta_time) override;
private:
	void move_walk(float delta_time);
	void move_run(float delta_time);
	void update_timer(float delta_time);

private:
	//�ǏՓˎ��Ƀ����_���ɓ�����鎞��
	float move_timer_;
	//�ړ����
	GSuint move_state_;
};
#endif//!PREDICTION_ENEMY_H_

