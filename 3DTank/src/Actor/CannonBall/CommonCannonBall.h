#ifndef COMMON_CANNON_BALL_H_
#define COMMON_CANNON_BALL_H_

#include "CannonBall.h"

class CommonCannonBall : public CannonBall
{
public:
    //コンストラクタ、生成位置と着弾予定位置
    CommonCannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination);

    virtual void react(Actor& other) override;
private:
    virtual void move(float delta_time) override;

};
#endif//!COMMON_CANNON_BALL_H_

