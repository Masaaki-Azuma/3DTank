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

    //€–S‚µ‚Ä‚¢‚é‚©H
	bool is_dead() const;
	//Õ“Ë”»’è}Œ`‚ğæ“¾
	BoundingSphere collider() const;
	//Õ“Ë‚µ‚Ä‚¢‚é‚©H
	bool is_collide(const Actor& other) const;

protected:
	//ƒ[ƒ‹ƒh
	IWorld* world_{ nullptr };
	//ˆÊ’uA‰ñ“]AŠgkî•ñ
	GStransform transform_;
	//‹«ŠE‹…
	BoundingSphere collider_;

	//€–Sƒtƒ‰ƒO
	bool is_dead_{ false };
};
#endif//!ACTOR_H_

