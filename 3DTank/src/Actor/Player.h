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
    //移動
    void move(float delta_time);
    //自由落下
    void free_fall(float delta_time);
    //弾の発射
    void shoot();
    //地形との押し出し判定
    void collide_field();
    //アクターとの押し出し判定
    void collide_actor(Actor& other);
};
#endif//!PLAYER_H_

