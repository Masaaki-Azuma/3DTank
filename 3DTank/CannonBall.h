#ifndef CANNON_BALL_H_
#define CANNON_BALL_H_

#include "Actor.h"

//�^���N�����C�ۃN���X
class CannonBall :
    public Actor
{
public:
    CannonBall(const GSvector3& position, const GSvector3& velocity);
    void update(float delta_time) override;
    void draw() const override;

private:
    GSvector3 velocity_;  //���ݑ��x
};
#endif//!CANNON_BALL_H_
