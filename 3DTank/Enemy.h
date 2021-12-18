#ifndef ENEMY_H_
#define ENEMY_H_

#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy(IWorld* world, const GSvector3& position);
	virtual ~Enemy() = default;

	virtual void update(float delta_time) override final;
	virtual void draw() const override final;
	virtual void react(Actor& other) override;
protected:
	//移動
	virtual void move(float delta_time);
	//弾を発射
	virtual void shoot(float delta_time);
	//壁に衝突時の挙動
	virtual void react_wall();
private:
	//重力を作用
	void free_fall(float delta_time);
	//地形との衝突判定
	void collide_field();

protected:
	float shot_timer_{ 0.0f };
	GSuint mesh_;
};
#endif//!ENEMY_H_

