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
	//二者の衝突判定が有効か？
	if (enable_collider_ && other.enable_collider_) {
		//衝突していたら衝突処理をする
		if (is_collide(other)) {
			//二者の衝突処理
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

const GSvector3& Actor::velocity() const
{
	return velocity_;
}

BoundingSphere Actor::collider() const
{
	return collider_.transform(transform_.localToWorldMatrix());
}
