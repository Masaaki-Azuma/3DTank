#include "CannonBall.h"
#include "IWorld.h"
#include "Stage.h"
#include "Assets.h"

const float Gravity{ -0.02f };
const float CannonVerticalSpeed{ 0.8f };  //�e�̉��������x
const float CannonVelocityFactor{ -2 * CannonVerticalSpeed / Gravity };  //�e�̐������x�����肷��W���A= -2*CannonVerticalSpeed/CannonBall::Gravity

CannonBall::CannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination, const std::string& tag)
{
	world_ = world;
	name_ = "CannonBall";
	tag_ = tag;
	transform_.position(position);
	collider_ = BoundingSphere{ 1.0f };
	//�����ʒu�ƒ��e�\��ʒu���珉���x���v�Z
	GSvector3 direction = destination - position;
	direction.y = 0.0f;
	velocity_ = direction / CannonVelocityFactor;
	velocity_.y = CannonVerticalSpeed;
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
	//�G�e�����@�ɓ������������
	if (tag_ == "EnemyCannonBallTag" && other.tag() == "PlayerTag") {
		die();
	}
}

void CannonBall::move(float delta_time)
{
	//�d�͂���p
	velocity_.y += Gravity * delta_time;
	//�ړ��ʂ𔽉f
	transform_.translate(velocity_ * delta_time);
}

void CannonBall::collide_field()
{
	//�n�`�ɓ���������폜
	if (world_->stage().collide(collider())) {
		die();
	}
}
