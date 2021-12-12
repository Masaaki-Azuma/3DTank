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
    void move(float delta_time);
    void free_fall(float delta_time);
    void shoot();
    void collide_field();
};
#endif//!PLAYER_H_

