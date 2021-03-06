#include "BlastCannonBall.h"
#include "PlayScene/IWorld.h"
#include "PlayScene/Stage.h"
#include "../Blast.h"
#include "Assets.h"

const float Gravity{ -0.01f };
const float CannonVerticalSpeed{ 0.7f };  //弾の鉛直初速度
const float CannonVelocityFactor{ -2 * CannonVerticalSpeed / Gravity };  ////着弾までにかかる時間、弾の水平速度を決定する係数、= -2*CannonVerticalSpeed/CannonBall::Gravity

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
	//敵弾が自機に当たったら消滅
	if (other.tag() == "PlayerTag") {
		world_->add_actor(new Blast{ transform_.position() });
		die();
	}
}

void BlastCannonBall::move(float delta_time)
{
	//重力を作用
	velocity_.y += Gravity * delta_time;
	//移動量を反映
	transform_.translate(velocity_ * delta_time);
}

void BlastCannonBall::collide_field()
{
	//地形に当たったら削除
	if (world_->stage().collide(collider())) {
		world_->add_actor(new Blast{ transform_.position() });
		die();
	}
}
