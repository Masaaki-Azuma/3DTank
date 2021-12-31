#ifndef ENEMY_H_
#define ENEMY_H_

#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy(IWorld* world, const GSvector3& position, float shot_interval = 90.0f, float cannon_range = 16.0f);
	virtual ~Enemy() = default;

	virtual void update(float delta_time) override final;
	virtual void draw() const override final;
	virtual void react(Actor& other) override;
protected:
	//移動
	virtual void move(float delta_time);
	//弾を発射
	virtual void shoot(float delta_time);
	//弾を生成
	virtual void generate_cannon_ball(const GSvector3& position, const GSvector3& destination);
	//壁に衝突時の挙動
	virtual void react_wall();
private:
	//重力を作用
	void free_fall(float delta_time);
	//地形との衝突判定
	void collide_field();

	//
	void collide_actor(Actor& other);
protected:
	GSuint mesh_;
	float shot_timer_{ 0.0f };
	const float ShotInterval; //弾の発射間隔
	const float CannonRange; //弾が届く距離
	const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };  //弾を撃つ位置のオフセット
};
#endif//!ENEMY_H_

