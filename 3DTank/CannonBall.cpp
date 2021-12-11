#include "CannonBall.h"
#include "IWorld.h"
#include "Field.h"

const float Gravity{ -0.02f };

CannonBall::CannonBall(IWorld* world, const GSvector3& position, const GSvector3& velocity):
	velocity_{velocity}
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
}

void CannonBall::draw() const
{
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(1);
	glPopMatrix();

	//ForDebug
	collider().draw();
}

void CannonBall::move(float delta_time)
{
	//重力を作用
	velocity_.y += Gravity;
	//移動量を反映
	transform_.translate(velocity_ * delta_time);
}

void CannonBall::collide_field()
{
	//地形に当たったら削除
	if (world_->field().collide(collider())) {
		die();
	}
}
