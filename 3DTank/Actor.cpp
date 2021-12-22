#include "Actor.h"

void Actor::update(float delta_time)
{
}

void Actor::draw() const
{
}

void Actor::draw_gui() const
{
}

void Actor::react(Actor& other)
{
}

void Actor::die()
{
	is_dead_ = true;
}

bool Actor::is_dead() const
{
	return is_dead_;
}

void Actor::collide(Actor& other)
{
	//��҂̏Փ˔��肪�L�����H
	if (enable_collider_ && other.enable_collider_) {
		//�Փ˂��Ă�����Փˏ���������
		if (is_collide(other)) {
			//��҂̏Փˏ���
			react(other);
			other.react(*this);
		}
	}
	
}

bool Actor::is_collide(const Actor& other) const
{
	return collider().intersects(other.collider());
}

const std::string& Actor::name() const
{
	return name_;
}

const std::string& Actor::tag() const
{
	return tag_;
}

const GStransform& Actor::transform() const
{
	return transform_;
}

BoundingSphere Actor::collider() const
{
	return collider_.transform(transform_.localToWorldMatrix());
}
