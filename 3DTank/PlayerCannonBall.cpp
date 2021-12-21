#include "PlayerCannonBall.h"
#include "Assets.h"

const float Gravity{ -0.02f };
const float CannonVerticalSpeed{ 0.8f };  //�e�̉��������x
const float CannonVelocityFactor{ -2 * CannonVerticalSpeed / Gravity };  ////���e�܂łɂ����鎞�ԁA�e�̐������x�����肷��W���A= -2*CannonVerticalSpeed/CannonBall::Gravity

PlayerCannonBall::PlayerCannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination):
	CannonBall{world, position, destination}
{
	name_ = "PlayerCannonBall";
	tag_ = "PlayerCannonBallTag";
	mesh_ = Mesh_CannonBall;

	GSvector3 relative_position = destination - position;
	velocity_ = relative_position / CannonVelocityFactor;
	velocity_.y = CannonVerticalSpeed;
}

void PlayerCannonBall::react(Actor& other)
{
	//���@�e���G�ɓ������������
	if (other.tag() == "EnemyTag") {
		die();
	}
}

void PlayerCannonBall::move(float delta_time)
{
	//�d�͂���p
	velocity_.y += Gravity * delta_time;
	//�ړ��ʂ𔽉f
	transform_.translate(velocity_ * delta_time);
}
