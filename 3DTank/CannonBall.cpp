#include "CannonBall.h"
#include "IWorld.h"
#include "Stage.h"
#include "Assets.h"

const float Gravity{ -0.02f };

CannonBall::CannonBall(IWorld* world, const GSvector3& position, const GSvector3& velocity, const std::string& tag)
{
	world_ = world;
	name_ = "CannonBall";
	tag_ = tag;
	transform_.position(position);
	velocity_ = velocity;
	collider_ = BoundingSphere{ 1.0f };
}

void CannonBall::update(float delta_time)
{
	//ˆÚ“®
	move(delta_time);
	//’nŒ`‚Æ‚ÌÕ“Ëˆ—
	collide_field();
}

void CannonBall::draw() const
{
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(Mesh_CannonBall);
	glPopMatrix();

	//ForDebug
	collider().draw();
}

void CannonBall::react(Actor& other)
{
	//©‹@’e‚ª“G‚É“–‚½‚Á‚½‚çÁ–Å
	if (tag_ == "PlayerCannonBallTag" && other.tag() == "EnemyTag") {
		die();
	}
	//“G’e‚ª©‹@‚É“–‚½‚Á‚½‚çÁ–Å
	if (tag_ == "EnemyCannonBallTag" && other.tag() == "PlayerTag") {
		die();
	}
}

void CannonBall::move(float delta_time)
{
	//d—Í‚ğì—p
	velocity_.y += Gravity * delta_time;
	//ˆÚ“®—Ê‚ğ”½‰f
	transform_.translate(velocity_ * delta_time);
}

void CannonBall::collide_field()
{
	//’nŒ`‚É“–‚½‚Á‚½‚çíœ
	if (world_->stage().collide(collider())) {
		die();
	}
}
