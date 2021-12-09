#include "Player.h"

const float MoveSpeed{ 0.2f };
Player::Player(const GSvector3& position)
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
	GSvector3 direction{ 0.0f, 0.0f, 0.0f };
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
	GSvector3 velocity = direction.normalized() * MoveSpeed * delta_time;
	transform_.translate(velocity, GStransform::Space::World);
}
