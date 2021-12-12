#include "CannonBall.h"
#include "IWorld.h"
#include "Field.h"
#include "Assets.h"

const float Gravity{ -0.02f };

CannonBall::CannonBall(IWorld* world, const GSvector3& position, const GSvector3& velocity, const std::string& tag)
{
	world_ = world;
	name_ = "CannonBall";
	tag_ = tag;
	transform_.position(position);
	velocity_ = velocity;
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
	gsDrawMesh(Mesh_CannonBall);
	glPopMatrix();

	//ForDebug
	collider().draw();
}

void CannonBall::react(Actor& other)
{
	//���@�e���G�ɓ������������
	if (tag_ == "PlayerCannonBallTag" && other.tag() == "EnemyTag") {
		die();
	}
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
