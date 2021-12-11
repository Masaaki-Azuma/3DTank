#include "Actor.h"

void Actor::update(float delta_time)
{
}

void Actor::draw() const
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

bool Actor::is_collide(const Actor& other) const
{
	return collider().intersects(other.collider());
}

BoundingSphere Actor::collider() const
{
	return collider_.transform(transform_.localToWorldMatrix());
}
