#include "Player.h"

Player::Player(const GSvector3& position)
{
	transform_.position(position);
}

void Player::update(float delta_time)
{

}

void Player::draw() const
{
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(0);
	glPopMatrix();
}
