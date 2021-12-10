#include "Player.h"
#include "CannonBall.h"
#include "IWorld.h"

const float MoveSpeed{ 0.2f };
Player::Player(IWorld* world, const GSvector3& position):
	world_{world}
{
	collider_ = BoundingSphere{ 2.0f, GSvector3{0.0f, 1.0f, 0.0f} };
	transform_.position(position);
}

void Player::update(float delta_time)
{
	//Ú®
	move(delta_time);
	//CÛÌ­Ë
	shoot();
}

void Player::draw() const
{
	//bVÌ`æ
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(0);
	glPopMatrix();

	//ForDebug
	//«EÌ`æ
	collider().draw();
}

void Player::move(float delta_time)
{
	//Ú®ûü
	GSvector3 direction{ 0.0f, 0.0f, 0.0f };
	//WASDìÅÚ®
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
	//Ú®ÊÌZo
	GSvector3 velocity = direction.normalized() * MoveSpeed * delta_time;
	//Ú®Êð½f
	transform_.translate(velocity, GStransform::Space::World);
}

void Player::shoot()
{
	//eð­Ë
	if (gsGetKeyTrigger(GKEY_SPACE)) {
		//eÌûü
		GSvector3 direction{ 0.0f, 0.0f, 0.0f };
		if (gsGetKeyState(GKEY_RIGHT)) {
			direction.x += 1.0f;
		}
		if (gsGetKeyState(GKEY_LEFT)) {
			direction.x -= 1.0f;
		}
		if (gsGetKeyState(GKEY_UP)) {
			direction.z -= 1.0f;
		}
		if (gsGetKeyState(GKEY_DOWN)) {
			direction.z += 1.0f;
		}
		//eÌ¬x
		GSvector3 velocity = direction.normalized() * 0.2;
		//ãºûüÌÚ®ÊÍÅè
		velocity.y = 0.8f;
		//CÛð­Ë
		world_->add_actor(new CannonBall{ transform_.position(), velocity});
	}
}
