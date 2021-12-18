#ifndef ENEMY_H_
#define ENEMY_H_

#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy(IWorld* world, const GSvector3& position);
	virtual ~Enemy() = default;

	virtual void update(float delta_time) override;
	virtual void draw() const override;
	virtual void react(Actor& other) override;
private:
	//移動
	void move(float delta_time);
	//重力を作用
	void free_fall(float delta_time);
	//弾を発射
	void shoot(float delta_time);
	//地形との衝突判定
	void collide_field();
	//壁に衝突時の挙動
	void react_wall();

private:
	float shot_timer_{ 0.0f };
	GSuint mesh_;
};
#endif//!ENEMY_H_

