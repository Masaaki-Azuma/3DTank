#include "CannonBall.h"

CannonBall::CannonBall(const GSvector3& position, const GSvector3& velocity):
	velocity_{velocity}
{
	transform_.position(position);
}

void CannonBall::update(float delta_time)
{

}

void CannonBall::draw() const
{
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(1);
	glPopMatrix();
}
