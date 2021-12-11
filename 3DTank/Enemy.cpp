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
	//�ړ�
	move(delta_time);
	//���R����
	free_fall(delta_time);
	//�e�𔭎�
	shoot(delta_time);
	//�n�`�ƏՓ˔���
	collide_field();
}

void Enemy::draw() const
{
	//���b�V���̕`��
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(Mesh_Enemy);
	glPopMatrix();

	//ForDebug
	//���E���̕`��
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
