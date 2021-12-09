#ifndef ACTOR_H_
#define ACTOR_H_

#include <gslib.h>
#include <GStransform.h>
class Actor
{
public:
	Actor() = default;
	virtual ~Actor() = default;

	virtual void update(float delta_time);
	virtual void draw() const;

	bool is_dead() const;

protected:
	//ˆÊ’uA‰ñ“]AŠgkî•ñ
	GStransform transform_;
	//‹«ŠE‹…


	//€–Sƒtƒ‰ƒO
	bool is_dead_{ false };
};
#endif//!ACTOR_H_

