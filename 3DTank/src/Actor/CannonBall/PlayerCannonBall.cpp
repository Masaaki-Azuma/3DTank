#include "PlayerCannonBall.h"
#include "Assets.h"

const float Gravity{ -0.03f };
const float CannonVerticalSpeed{ 1.0f };  //弾の鉛直初速度
const float CannonVelocityFactor{ -2 * CannonVerticalSpeed / Gravity };  ////着弾までにかかる時間、弾の水平速度を決定する係数、= -2*CannonVerticalSpeed/CannonBall::Gravity

PlayerCannonBall::PlayerCannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination):
	CannonBall{world, position, destination}
{
	name_ = "PlayerCannonBall";
	tag_ = "PlayerCannonBallTag";
	collider_ = BoundingSphere{ 1.2f }; //プレイヤー弾は敵弾より大き目
	mesh_ = Mesh_PlayerCannonBall;

	GSvector3 relative_position = destination - position;
	velocity_ = relative_position / CannonVelocityFactor;
	velocity_.y = CannonVerticalSpeed;
}

void PlayerCannonBall::react(Actor& other)
{
	//自機弾が敵に当たったら消滅
	if (other.tag() == "EnemyTag") {
		generate_smoke();
		die();
	}
}

void PlayerCannonBall::move(float delta_time)
{
	//重力を作用
	velocity_.y += Gravity * delta_time;
	//移動量を反映
	transform_.translate(velocity_ * delta_time);
}
