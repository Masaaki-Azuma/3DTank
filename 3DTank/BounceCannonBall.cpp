#include "BounceCannonBall.h"
#include "IWorld.h"
#include "Stage.h"
#include "Assets.h"

const float Gravity{ -0.04f };
const float CannonVerticalSpeed{ 1.0f };  //弾の鉛直初速度
const float CannonVelocityFactor{ -2 * CannonVerticalSpeed / Gravity };  ////着弾までにかかる時間 -2*CannonVerticalSpeed/CannonBall::Gravity
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
	//敵弾が自機に当たったら消滅
	if (other.tag() == "PlayerTag") {
		die();
	}
}

void BounceCannonBall::move(float delta_time)
{
	//重力を作用
	velocity_.y += Gravity * delta_time;
	//移動量を反映
	transform_.translate(velocity_ * delta_time);
}

void BounceCannonBall::collide_field()
{
	GSvector3 center;
	//地形に当たったか？
	if (world_->stage().collide(collider(), &center)) {
		bounce_count++;
		//地面に3回着いたら爆発
		if (bounce_count >= MaxBounceCount) {
			die();
			//爆発判定を生成

			return;
		}
		//地形に埋まらないよう押し戻し
		transform_.position(center);
		//上にバウンド
		velocity_.y = velocity_.y * -0.94f;
	}
}
