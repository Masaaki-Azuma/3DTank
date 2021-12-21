#include "BounceCannonBall.h"
#include "IWorld.h"
#include "Stage.h"
#include "Assets.h"

const float Gravity{ -0.04f };
const float CannonVerticalSpeed{ 1.0f };  //�e�̉��������x
const float CannonVelocityFactor{ -2 * CannonVerticalSpeed / Gravity };  ////���e�܂łɂ����鎞�� -2*CannonVerticalSpeed/CannonBall::Gravity
const int MaxBounceCount{ 3 };


BounceCannonBall::BounceCannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination):
	CannonBall{world, position, destination}
{
	name_ = "BounceCannonBall";
	tag_ = "EnemyCannonBallTag";
	mesh_ = Mesh_CannonBall;

	GSvector3 relative_position = destination - position;
	velocity_ = relative_position / CannonVelocityFactor / 2;
	velocity_.y = CannonVerticalSpeed;
}

void BounceCannonBall::react(Actor& other)
{
	//�G�e�����@�ɓ������������
	if (other.tag() == "PlayerTag") {
		die();
	}
}

void BounceCannonBall::move(float delta_time)
{
	//�d�͂���p
	velocity_.y += Gravity * delta_time;
	//�ړ��ʂ𔽉f
	transform_.translate(velocity_ * delta_time);
}

void BounceCannonBall::collide_field()
{
	GSvector3 center;
	//�n�`�ɓ����������H
	if (world_->stage().collide(collider(), &center)) {
		bounce_count++;
		//�n�ʂ�3�񒅂����甚��
		if (bounce_count >= MaxBounceCount) {
			die();
			//��������𐶐�

			return;
		}
		//�n�`�ɖ��܂�Ȃ��悤�����߂�
		transform_.position(center);
		//��Ƀo�E���h
		velocity_.y = velocity_.y * -0.94f;
	}
}
