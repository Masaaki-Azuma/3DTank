#include "CannonBall.h"
#include <GSeffect.h>
#include "PlayScene/IWorld.h"
#include "PlayScene/Stage.h"
#include "../Blast.h"
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
}

void CannonBall::update(float delta_time)
{
	//移動
	move(delta_time);
	//地形との衝突処理
	collide_field();
	//ステージ外で死亡
	die_outside();
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
	
}

void CannonBall::collide_field()
{
	//地形に当たったら削除
	if (world_->stage().collide(collider())) {
		generate_smoke();
		die();
	}
}

void CannonBall::die_outside()
{
	//一定高度を下回ったら削除
	if (transform_.position().y <= -100.0f) {
		die();
	}
}

void CannonBall::generate_smoke()
{
	world_->add_actor(new Blast{ transform_.position() });
}

