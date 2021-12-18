#ifndef CANNON_BALL_H_
#define CANNON_BALL_H_

#include "Actor.h"

//�^���N�����C�ۃN���X
class CannonBall :
    public Actor
{
public:
    //�R���X�g���N�^�A�����ʒu�Ə����x
    //CannonBall(IWorld* world, const GSvector3& position, const GSvector3& velocity, const std::string& tag = "CannonBallTag");
    //�R���X�g���N�^�A�����ʒu�ƒ��e�\��ʒu
    CannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination, const std::string& tag = "CannonBallTag");

    virtual void update(float delta_time) override;
    virtual void draw() const override;
    virtual void react(Actor& other) override;

private:
    //�ړ�
    void move(float delta_time);
    //�n�`�Ƃ̏Փˏ���
    void collide_field();

};
#endif//!CANNON_BALL_H_

