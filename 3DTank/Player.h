#ifndef PLAYER_H_
#define PLAYER_H_

#include "Actor.h"

class Player :
    public Actor
{
public:
    Player(const GSvector3& position);
    virtual void update(float delta_time) override;
    virtual void draw() const override;

private:
    void move(float delta_time);
};
#endif//!PLAYER_H_

