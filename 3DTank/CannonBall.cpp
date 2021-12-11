#include "CannonBall.h"
#include "IWorld.h"
#include "Field.h"

const float Gravity{ -0.02f };

CannonBall::CannonBall(IWorld* world, const GSvector3& position, const GSvector3& velocity):
	velocity_{velocity}
{
	world_ = world;
	transform_.position(position);
	collider_ = BoundingSphere{ 1.0f };
}

void CannonBall::update(float delta_time)
{
	//�ړ�
	move(delta_time);
	//�n�`�Ƃ̏Փˏ���
	collide_field();
}

void CannonBall::draw() const
{
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(1);
	glPopMatrix();

	//ForDebug
	collider().draw();
}

void CannonBall::move(float delta_time)
{
	//�d�͂���p
	velocity_.y += Gravity;
	//�ړ��ʂ𔽉f
	transform_.translate(velocity_ * delta_time);
}

void CannonBall::collide_field()
{
	//�n�`�ɓ���������폜
	if (world_->field().collide(collider())) {
		die();
	}
}
