#include "BlastCannonBall.h"
#include "PlayScene/IWorld.h"
#include "PlayScene/Stage.h"
#include "../Blast.h"
#include "Assets.h"

const float Gravity{ -0.01f };
const float CannonVerticalSpeed{ 0.7f };  //�e�̉��������x
const float CannonVelocityFactor{ -2 * CannonVerticalSpeed / Gravity };  ////���e�܂łɂ����鎞�ԁA�e�̐������x�����肷��W���A= -2*CannonVerticalSpeed/CannonBall::Gravity

BlastCannonBall::BlastCannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination):
	CannonBall{world, position, destination}
{
	name_ = "BlastCannonBall";
	tag_ = "EnemyCannonTag";
	mesh_ = Mesh_CannonBall;

	GSvector3 relative_position = destination - position;
	velocity_ = relative_position / CannonVelocityFactor;
	velocity_.y = CannonVerticalSpeed;
}

void BlastCannonBall::react(Actor& other)
{
	//�G�e�����@�ɓ������������
	if (other.tag() == "PlayerTag") {
		world_->add_actor(new Blast{ transform_.position() });
		die();
	}
}

void BlastCannonBall::move(float delta_time)
{
	//�d�͂���p
	velocity_.y += Gravity * delta_time;
	//�ړ��ʂ𔽉f
	transform_.translate(velocity_ * delta_time);
}

void BlastCannonBall::collide_field()
{
	//�n�`�ɓ���������폜
	if (world_->stage().collide(collider())) {
		world_->add_actor(new Blast{ transform_.position() });
		die();
	}
}
