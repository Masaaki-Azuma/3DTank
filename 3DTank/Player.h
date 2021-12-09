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
};
#endif//!PLAYER_H_

