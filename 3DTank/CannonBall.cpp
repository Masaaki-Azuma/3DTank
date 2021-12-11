#include "CannonBall.h"

const float Gravity{ -0.02f };
CannonBall::CannonBall(const GSvector3& position, const GSvector3& velocity):
	velocity_{velocity}
{
	transform_.position(position);
}

void CannonBall::update(float delta_time)
{
	move(delta_time);

	//ForDebug
	//â∫Ç…çsÇ¡ÇΩÇÁçÌèú
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

void CannonBall::move(float delta_time)
{
	//èdóÕÇçÏóp
	velocity_.y += Gravity;
	//à⁄ìÆó ÇîΩâf
	transform_.translate(velocity_ * delta_time);
}
