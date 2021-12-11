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
	//���ɍs������폜
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
	//�d�͂���p
	velocity_.y += Gravity;
	//�ړ��ʂ𔽉f
	transform_.translate(velocity_ * delta_time);
}
