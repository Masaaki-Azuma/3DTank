#ifndef BLAST_CANNON_BALL_H_
#define BLAST_CANNON_BALL_H_

#include "CannonBall.h"

class BlastCannonBall : public CannonBall
{
public:
	BlastCannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination);
	//アクターとの衝突リアクション
	virtual void react(Actor& other) override;
private:
	//移動
	virtual void move(float delta_time);
	//地形との衝突判定
	virtual void collide_field();
};
#endif//!BLAST_CANNON_BALL_H_

