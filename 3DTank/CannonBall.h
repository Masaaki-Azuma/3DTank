#ifndef CANNON_BALL_H_
#define CANNON_BALL_H_

#include "Actor.h"

//タンクが撃つ砲丸クラス
class CannonBall :
    public Actor
{
public:
    CannonBall(IWorld* world, const GSvector3& position, const GSvector3& velocity, const std::string& tag = "CannonBallTag");
    virtual void update(float delta_time) override;
    virtual void draw() const override;
    virtual void react(Actor& other) override;

private:
    //移動
    void move(float delta_time);
    //地形との衝突処理
    void collide_field();

};
#endif//!CANNON_BALL_H_

