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
	//ˆÚ“®
	move(delta_time);
	//©—R—‰º
	free_fall(delta_time);
	//’e‚ğ”­Ë
	shoot(delta_time);
	//’nŒ`‚ÆÕ“Ë”»’è
	collide_field();
}

void Enemy::draw() const
{
	//ƒƒbƒVƒ…‚Ì•`‰æ
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(Mesh_Enemy);
	glPopMatrix();

	//ForDebug
	//‹«ŠE‹…‚Ì•`‰æ
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
