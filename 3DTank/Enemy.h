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
	//ˆÚ“®
	virtual void move(float delta_time);
	//’e‚ğ”­Ë
	virtual void shoot(float delta_time);
	//’e‚ğ¶¬
	virtual void generate_cannon_ball(const GSvector3& position, const GSvector3& destination);
	//•Ç‚ÉÕ“Ë‚Ì‹““®
	virtual void react_wall();
private:
	//d—Í‚ğì—p
	void free_fall(float delta_time);
	//’nŒ`‚Æ‚ÌÕ“Ë”»’è
	void collide_field();

	//
	void collide_actor(Actor& other);
protected:
	GSuint mesh_;
	float shot_timer_{ 0.0f };
	const float ShotInterval; //’e‚Ì”­ËŠÔŠu
	const float CannonRange; //’e‚ª“Í‚­‹——£
};
#endif//!ENEMY_H_

