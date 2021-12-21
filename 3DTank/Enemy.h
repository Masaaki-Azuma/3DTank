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
	//�ړ�
	virtual void move(float delta_time);
	//�e�𔭎�
	virtual void shoot(float delta_time);
	//�e�𐶐�
	virtual void generate_cannon_ball(const GSvector3& position, const GSvector3& destination);
	//�ǂɏՓˎ��̋���
	virtual void react_wall();
private:
	//�d�͂���p
	void free_fall(float delta_time);
	//�n�`�Ƃ̏Փ˔���
	void collide_field();

	//
	void collide_actor(Actor& other);
protected:
	GSuint mesh_;
	float shot_timer_{ 0.0f };
	const float ShotInterval; //�e�̔��ˊԊu
	const float CannonRange; //�e���͂�����
};
#endif//!ENEMY_H_

