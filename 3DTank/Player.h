#ifndef PLAYER_H_
#define PLAYER_H_

#include "Actor.h"

class IWorld;

class Player :
    public Actor
{
public:
    Player(IWorld* world, const GSvector3& position);
    virtual void update(float delta_time) override;
    virtual void draw() const override;
    virtual void react(Actor& other) override;

private:
    //�ړ�
    void move(float delta_time);
    //���R����
    void free_fall(float delta_time);
    //�e�̔���
    void shoot();
    //�n�`�Ƃ̉����o������
    void collide_field();
    //�A�N�^�[�Ƃ̉����o������
    void collide_actor(Actor& other);
};
#endif//!PLAYER_H_

