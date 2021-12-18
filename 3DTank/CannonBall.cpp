#include "CannonBall.h"
#include "IWorld.h"
#include "Stage.h"
#include "Assets.h"

const float Gravity{ -0.02f };
const float CannonVerticalSpeed{ 0.8f };  //弾の鉛直初速度
const float CannonVelocityFactor{ -2 * CannonVerticalSpeed / Gravity };  //弾の水平速度を決定する係数、= -2*CannonVerticalSpeed/CannonBall::Gravity

CannonBall::CannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination, const std::string& tag)
{
	world_ = world;
	name_ = "CannonBall";
	tag_ = tag;
	transform_.position(position);
	collider_ = BoundingSphere{ 1.0f };
	//生成位置と着弾予定位置から初速度を計算
	GSvector3 direction = destination - position;
	direction.y = 0.0f;
	velocity_ = direction / CannonVelocityFactor;
	velocity_.y = CannonVerticalSpeed;
}

void CannonBall::update(float delta_time)
{
	//移動
	move(delta_time);
	//地形との衝突処理
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
	//自機弾が敵に当たったら消滅
	if (tag_ == "PlayerCannonBallTag" && other.tag() == "EnemyTag") {
		die();
	}
	//敵弾が自機に当たったら消滅
	if (tag_ == "EnemyCannonBallTag" && other.tag() == "PlayerTag") {
		die();
	}
}

void CannonBall::move(float delta_time)
{
	//重力を作用
	velocity_.y += Gravity * delta_time;
	//移動量を反映
	transform_.translate(velocity_ * delta_time);
}

void CannonBall::collide_field()
{
	//地形に当たったら削除
	if (world_->stage().collide(collider())) {
		die();
	}
}
