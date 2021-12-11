#ifndef CANNON_BALL_H_
#define CANNON_BALL_H_

#include "Actor.h"

//タンクが撃つ砲丸クラス
class CannonBall :
    public Actor
{
public:
    CannonBall(IWorld* world, const GSvector3& position, const GSvector3& velocity);
    void update(float delta_time) override;
    void draw() const override;
private:
    //移動
    void move(float delta_time);

private:
    GSvector3 velocity_;  //現在速度
};
#endif//!CANNON_BALL_H_

