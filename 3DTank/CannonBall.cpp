#include "CannonBall.h"

const float Gravity{ -0.02f };

CannonBall::CannonBall(IWorld* world, const GSvector3& position, const GSvector3& velocity):
	velocity_{velocity}
{
	world_ = world;
	transform_.position(position);
}

void CannonBall::update(float delta_time)
{
	move(delta_time);

	//ForDebug
	//下に行ったら削除
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
	//重力を作用
	velocity_.y += Gravity;
	//移動量を反映
	transform_.translate(velocity_ * delta_time);
}
