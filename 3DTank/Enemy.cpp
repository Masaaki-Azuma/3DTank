#include "Enemy.h"
#include "Assets.h"

Enemy::Enemy(IWorld* world, const GSvector3& position)
{
	world_ = world;
	transform_.position(position);
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, 1.9f, 0.0f} };
}

void Enemy::update(float delta_time)
{
	//移動
	move(delta_time);
	//自由落下
	free_fall(delta_time);
	//弾を発射
	shoot(delta_time);
	//地形と衝突判定
	collide_field();
}

void Enemy::draw() const
{
	//メッシュの描画
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(Mesh_Enemy);
	glPopMatrix();

	//ForDebug
	//境界球の描画
	collider().draw();
}

void Enemy::move(float delta_time)
{
}

void Enemy::free_fall(float delta_time)
{
}

void Enemy::shoot(float delta_time)
{
}

void Enemy::collide_field()
{
}
