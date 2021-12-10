#include "Player.h"
#include "CannonBall.h"
#include "IWorld.h"
#include "Line.h"
#include "Assets.h"

const float MoveSpeed{ 0.2f };
const float Gravity{ -0.05f };
//const float PlayerHeight{ 1.9f };
const float FootOffset{ 0.1f };
Player::Player(IWorld* world, const GSvector3& position):
	world_{world}
{
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, 1.9f, 0.0f} };
	transform_.position(position);
}

void Player::update(float delta_time)
{
	//ˆÚ“®
	move(delta_time);
	//d—Í‚É‚æ‚éŽ©—R—Ž‰º
	free_fall(delta_time);
	//–CŠÛ‚Ì”­ŽË
	shoot();

	//’nŒ`‚Æ‚ÌˆÊ’u•â³
	//•Ç‚Æ‚ÌÕ“Ë”»’è
	GSvector3 center;
	bool is_collide_wall = gsOctreeCollisionSphere(
		gsGetOctree(Octree_Collide), &collider().center(), collider().radius(), &center);
	if (is_collide_wall) {
		center.y = transform_.position().y;
		transform_.position(center);
	}
	////’n–Ê‚Æ‚ÌÕ“Ë”»’è
	Line line{ transform_.position() + GSvector3{0.0f, collider().radius(), 0.0f},  transform_.position() + GSvector3{ 0.0f, -FootOffset, 0.0f } };
	GSvector3 intersect;
	GSplane plane;
	bool is_collider_floor = gsOctreeCollisionLine(
		gsGetOctree(Octree_Collide), &line.start(), &line.end(), &intersect, &plane
	);
	if (is_collider_floor) {
		GSvector3 position = line.start();
		position.y = intersect.y - FootOffset;
		transform_.position(position);
		velocity_.y = 0.0f;
	}
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
	//x,zŽ²•ûŒü‚ÌˆÚ“®—Ê‚ð•Û‘¶
	velocity_.x = velocity.x;
	velocity_.z = velocity.z;
	//…•½•ûŒü‚ÌˆÚ“®—Ê‚ð”½‰f
	transform_.translate(velocity, GStransform::Space::World);
}

void Player::free_fall(float delta_time)
{
	//d—Í‚ðì—p
	velocity_.y += Gravity * delta_time;
	//ã‰º•ûŒü‚ÌˆÚ“®—Ê‚ð”½‰f
	transform_.translate(GSvector3{ 0.0f, velocity_.y, 0.0f }, GStransform::Space::World);
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
