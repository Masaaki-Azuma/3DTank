#ifndef ACTOR_H_
#define ACTOR_H_

//#include <gslib.h>
#include <GStransform.h>
class Actor
{
public:
	Actor() = default;
	virtual ~Actor() = default;
	void update(float delta_time);
	void draw() const;

	bool is_dead() const;

private:
	//ˆÊ’uA‰ñ“]AŠgkî•ñ
	GStransform transform_;
	//€–Sƒtƒ‰ƒO
	bool is_dead_{ false };
};
#endif//!ACTOR_H_

