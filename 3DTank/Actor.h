#ifndef ACTOR_H_
#define ACTOR_H_

#include <gslib.h>
#include <GStransform.h>
#include <string>
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

	//���S����
	void die();
    //���S���Ă��邩�H
	bool is_dead() const;
	//�Փ˔���
	void collide(Actor& other);

	//�Փ˂��Ă��邩�H
	bool is_collide(const Actor& other) const;

	//���O���擾
	const std::string& name() const;
	//�^�O�����擾
	const std::string& tag() const;
	//�Փ˔���}�`���擾
	BoundingSphere collider() const;

protected:
	//���[���h
	IWorld* world_{ nullptr };
	//���O
	std::string name_;
	//�^�O��
	std::string tag_;
	//�ʒu�A��]�A�g�k���
	GStransform transform_;
	//�ړ���
	GSvector3 velocity_;
	//���E��
	BoundingSphere collider_;
	//���S�t���O
	bool is_dead_{ false };
};
#endif//!ACTOR_H_

