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
	//ˆÚ“®
	move(delta_time);
	//–CŠÛ‚Ì”­ŽË
	shoot();
}

void Player::draw() const
{
	//ƒƒbƒVƒ…‚Ì•`‰æ
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(0);
	glPopMatrix();

	//ForDebug
	//‹«ŠE‹…‚Ì•`‰æ
	collider().draw();
}

void Player::move(float delta_time)
{
	//ˆÚ“®•ûŒü
	GSvector3 direction{ 0.0f, 0.0f, 0.0f };
	//WASD‘€ì‚ÅˆÚ“®
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
	//ˆÚ“®—Ê‚ÌŽZo
	GSvector3 velocity = direction.normalized() * MoveSpeed * delta_time;
	//ˆÚ“®—Ê‚ð”½‰f
	transform_.translate(velocity, GStransform::Space::World);
}

void Player::shoot()
{
	//’e‚ð”­ŽË
	if (gsGetKeyTrigger(GKEY_SPACE)) {
		//’e‚Ì•ûŒü
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
		//’e‚Ì‘¬“x
		GSvector3 velocity = direction.normalized() * 0.2;
		//ã‰º•ûŒü‚ÌˆÚ“®—Ê‚ÍŒÅ’è
		velocity.y = 0.8f;
		//–CŠÛ‚ð”­ŽË
		world_->add_actor(new CannonBall{ transform_.position(), velocity});
	}
}
