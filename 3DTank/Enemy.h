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
	//�ړ�
	void move(float delta_time);
	//�d�͂���p
	void free_fall(float delta_time);
	//�e�𔭎�
	void shoot(float delta_time);
	//�n�`�Ƃ̏Փ˔���
	void collide_field();
	//�ǂɏՓˎ��̋���
	void react_wall();

private:
	float shot_timer_{ 0.0f };
	GSuint mesh_;
};
#endif//!ENEMY_H_

