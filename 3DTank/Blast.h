#ifndef BLAST_H_
#define BLAST_H_

#include "Actor.h"

//–CŠÛ”š”­Œã‚Ì”š•—ƒNƒ‰ƒX
class Blast : public Actor
{
public:
	Blast(const GSvector3& position);

	virtual void update(float delta_time) override;
	virtual void draw() const override;

private:
	float timer_{ 0.0f };
};
#endif//!BLAST_H_

