#ifndef CANNON_BALL_H_
#define CANNON_BALL_H_

#include "Actor.h"

//�^���N�����C�ۃN���X
class CannonBall : public Actor
{
public:
    //�R���X�g���N�^�A�����ʒu�ƒ��e�\��ʒu
    CannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination);

    virtual void update(float delta_time) override;
    virtual void draw() const override;
    virtual void react(Actor& other) override;

protected:
    //�ړ�
    virtual void move(float delta_time) = 0;
    //�n�`�Ƃ̏Փˏ���
    virtual void collide_field();
private:
    //�����x���Z�o
    //void calculate_velocity(const GSvector3& position, const GSvector3& destination);

protected:
    GSuint mesh_;
};
#endif//!CANNON_BALL_H_

