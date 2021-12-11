#ifndef ACTOR_H_
#define ACTOR_H_

#include <gslib.h>
#include <GStransform.h>
#include "BoundingSphere.h"

class IWorld;

class Actor
{
public:
	Actor() = default;
	virtual ~Actor() = default;

	virtual void update(float delta_time);
	virtual void draw() const;
	virtual void react(Actor& other);

    //���S���Ă��邩�H
	bool is_dead() const;
	//�Փ˔���}�`���擾
	BoundingSphere collider() const;
	//�Փ˂��Ă��邩�H
	bool is_collide(const Actor& other) const;

protected:
	//���[���h
	IWorld* world_{ nullptr };
	//�ʒu�A��]�A�g�k���
	GStransform transform_;
	//���E��
	BoundingSphere collider_;

	//���S�t���O
	bool is_dead_{ false };
};
#endif//!ACTOR_H_

