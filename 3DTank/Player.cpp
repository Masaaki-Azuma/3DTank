#include "Player.h"
#include "CannonBall.h"
#include "IWorld.h"

const float MoveSpeed{ 0.2f };
Player::Player(IWorld* world, const GSvector3& position):
	world_{world}
{
	transform_.position(position);
}

void Player::update(float delta_time)
{
	move(delta_time);
}

void Player::draw() const
{
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(0);
	glPopMatrix();
}

void Player::move(float delta_time)
{
	//�ړ�����
	GSvector3 direction{ 0.0f, 0.0f, 0.0f };
	//WASD����ňړ�
	if (gsGetKeyState(GKEY_D)) {
		direction.x += 1.0f;
	}
	if (gsGetKeyState(GKEY_A)) {
		direction.x -= 1.0f;
	}
	if (gsGetKeyState(GKEY_W)) {
		direction.z -= 1.0f;
	}
	if (gsGetKeyState(GKEY_S)) {
		direction.z += 1.0f;
	}
	//�ړ��ʂ̎Z�o
	GSvector3 velocity = direction.normalized() * MoveSpeed * delta_time;
	//�ړ��ʂ𔽉f
	transform_.translate(velocity, GStransform::Space::World);
}

void Player::shoot()
{

}
