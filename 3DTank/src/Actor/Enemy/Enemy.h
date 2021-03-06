#ifndef ENEMY_H_
#define ENEMY_H_

#include "../Actor.h"

class Enemy : public Actor
{
public:
	Enemy(IWorld* world, const GSvector3& position, float shot_interval = 90.0f, float cannon_range = 16.0f);
	virtual ~Enemy() = default;

	virtual void update(float delta_time) override final;
	virtual void draw() const override final;
	virtual void react(Actor& other) override;
protected:
	//Ú®
	virtual void move(float delta_time);
	//eð­Ë
	virtual void shoot(float delta_time);
	//eð¶¬
	virtual void generate_cannon_ball(const GSvector3& position, const GSvector3& destination);
	//GtFNgð¶¬
	void generate_smoke();
	//ÇÉÕËÌ®
	virtual void react_wall();
	//Ú®SEðÄ¶
	void play_moveSE();
private:
	//dÍðìp
	void free_fall(float delta_time);
	//n`ÆÌÕË»è
	void collide_field();
	//
	void collide_actor(Actor& other);
protected:
	GSuint mesh_;
	float shot_timer_{ 0.0f };
	const float ShotInterval; //eÌ­ËÔu
	const float CannonRange; //eªÍ­£
	const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };  //eðÂÊuÌItZbg
};
#endif//!ENEMY_H_

