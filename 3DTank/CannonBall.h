#ifndef CANNON_BALL_H_
#define CANNON_BALL_H_

#include "Actor.h"

//タンクが撃つ砲丸クラス
class CannonBall : public Actor
{
public:
    //コンストラクタ、生成位置と着弾予定位置
    CannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination);

    virtual void update(float delta_time) override;
    virtual void draw() const override;
    virtual void react(Actor& other) override;

protected:
    //移動
    virtual void move(float delta_time) = 0;
    //地形との衝突処理
    virtual void collide_field();
private:
    //初速度を算出
    //void calculate_velocity(const GSvector3& position, const GSvector3& destination);

protected:
    GSuint mesh_;
};
#endif//!CANNON_BALL_H_

