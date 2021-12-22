#include "Blast.h"
#include "Assets.h"

const float AnimationDuration{ 50.0f };
const float CollisionDuration{ 25.0f };
Blast::Blast(const GSvector3& position)
{
	name_ = "Blast";
	tag_ = "EnemyCannonBallTag";
	collider_ = BoundingSphere{ 5.0f };
	transform_.position(position);
}

void Blast::update(float delta_time)
{
	timer_ += delta_time;
	if (timer_ >= AnimationDuration) {
		die();
	}
	else if (timer_ >= CollisionDuration) {
		enable_collider_ = false;
	}
}

void Blast::draw() const
{
	//ƒƒbƒVƒ…‚Ì•`‰æ
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(Mesh_CannonBall);
	glPopMatrix();
	//ForDebug
	if (enable_collider_) collider().draw();
	//!ForDebug
}
