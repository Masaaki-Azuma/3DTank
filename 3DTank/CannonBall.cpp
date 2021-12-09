#include "CannonBall.h"

const float Gravity{ -0.02f };
CannonBall::CannonBall(const GSvector3& position, const GSvector3& velocity):
	velocity_{velocity}
{
	transform_.position(position);
}

void CannonBall::update(float delta_time)
{
	//d—Í‚ğì—p
	velocity_.y += Gravity;
	//ˆÚ“®—Ê‚ğ”½‰f
	transform_.translate(velocity_ * delta_time);

	//ForDebug
	//‰º‚És‚Á‚½‚çíœ
	if (transform_.position().y < -1) {
		is_dead_ = true;
	}
	//!ForDebug
}

void CannonBall::draw() const
{
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(1);
	glPopMatrix();
}
