#ifndef BLAST_CANNON_BALL_H_
#define BLAST_CANNON_BALL_H_

#include "CannonBall.h"

class BlastCannonBall : public CannonBall
{
public:
	BlastCannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination);
	//�A�N�^�[�Ƃ̏Փ˃��A�N�V����
	virtual void react(Actor& other) override;
private:
	//�ړ�
	virtual void move(float delta_time);
	//�n�`�Ƃ̏Փ˔���
	virtual void collide_field();
};
#endif//!BLAST_CANNON_BALL_H_

