#ifndef TARGET_SIGN_H_
#define TARGET_SIGN_H_

#include "Actor.h"
class TargetSign : public Actor
{
public:
	TargetSign(IWorld* world, const GSvector3& position);
	void update(float delta_time) override;
	void draw() const override;

private:
	GSvector3 offset_;
};
#endif//!TARGET_SIGN_H_

