#include "CannonBall.h"
#include <GSeffect.h>
#include "IWorld.h"
#include "Stage.h"
#include "Assets.h"

//const float Gravity{ -0.02f };
//const float CannonVerticalSpeed{ 0.8f };  //弾の鉛直初速度
//const float CannonVelocityFactor{ -2 * CannonVerticalSpeed / Gravity };  //弾の水平速度を決定する係数、= -2*CannonVerticalSpeed/CannonBall::Gravity

CannonBall::CannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination):
	mesh_{ Mesh_CannonBall }
{
	world_ = world;
	transform_.position(position);
	collider_ = BoundingSphere{ 1.0f };
	////生成位置と着弾予定位置から初速度を計算
	//calculate_velocity(position, destination);
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
	gsDrawMesh(mesh_);
	glPopMatrix();

	//ForDebug
	//collider().draw();
}

void CannonBall::react(Actor& other)
{
	
}
//HACK:おそらく派生クラスでも同じ処理になるが、Gravity定数をどうにかして一本にまとめられないだろうか？
void CannonBall::move(float delta_time)
{
	////重力を作用
	//velocity_.y += Gravity * delta_time;
	////移動量を反映
	//transform_.translate(velocity_ * delta_time);
}

void CannonBall::collide_field()
{
	//地形に当たったら削除
	if (world_->stage().collide(collider())) {
		GSvector3 position = transform_.position();
		gsPlayEffect(Effect_Smoke, &position);
		die();
	}
}

//相手のいる位置に弾が飛ぶよう速度を計算
//void CannonBall::calculate_velocity(const GSvector3& position, const GSvector3& destination)
//{
//	GSvector3 relative_position = destination - position;
//	relative_position.y = 0.0f;
//	//着弾までにかかる時間
//	const float CannonVelocityFactor = -2 * InitialVerticalSpeed / Gravity;
//	velocity_ = relative_position / CannonVelocityFactor;
//	velocity_.y = InitialVerticalSpeed;
//}
