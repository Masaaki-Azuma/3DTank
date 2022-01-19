#ifndef ACTOR_H_
#define ACTOR_H_

#include <gslib.h>
#include <GStransform.h>
#include <string>
#include "Figure/BoundingSphere.h"

class IWorld;

class Actor
{
public:
	Actor() = default;
	virtual ~Actor() = default;
	//�X�V
	virtual void update(float delta_time);
	//�`��
	virtual void draw() const;
	//GUI�`��
	virtual void draw_gui() const;
	//�Փ˃��A�N�V����
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
	//�ʒu�����擾
	const GStransform& transform() const;
	//���x���擾
	const GSvector3& velocity() const;
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
	//�Փ˔��肪�L�����H
	bool enable_collider_{ true };
	//���E��
	BoundingSphere collider_;
	//���S�t���O
	bool is_dead_{ false };
};
#endif//!ACTOR_H_
