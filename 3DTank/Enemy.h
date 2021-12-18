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
	//�ړ�
	virtual void move(float delta_time);
	//�e�𔭎�
	virtual void shoot(float delta_time);
	//�ǂɏՓˎ��̋���
	virtual void react_wall();
private:
	//�d�͂���p
	void free_fall(float delta_time);
	//�n�`�Ƃ̏Փ˔���
	void collide_field();

protected:
	float shot_timer_{ 0.0f };
	GSuint mesh_;
};
#endif//!ENEMY_H_

