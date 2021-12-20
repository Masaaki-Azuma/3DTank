#include "Enemy.h"
#include "IWorld.h"
#include "Stage.h"
#include "Line.h"
#include "CannonBall.h"
#include "Assets.h"

const float Gravity{ -0.02f };                     //d—Í‰Á‘¬“x
//const float EnemyHeight{ 2.0f };                   //‹«ŠE‹…’†S‚Ì‚‚³
const float FootOffset{ 0.1f };                    //’n–Ê‚Æ‚Ì“–‚½‚è”»’è—p‚Ì‘«Œ³ƒIƒtƒZƒbƒg
const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };  //’e‚ðŒ‚‚ÂˆÊ’u‚ÌƒIƒtƒZƒbƒg

Enemy::Enemy(IWorld* world, const GSvector3& position, float shot_inteval, float cannon_range):
	mesh_{Mesh_Enemy},
	ShotInterval{shot_inteval},
	CannonRange{cannon_range}
{
	world_ = world;
	name_ = "Enemy";
	tag_ = "EnemyTag";
	transform_.position(position);
}

void Enemy::update(float delta_time)
{
	//ˆÚ“®
	move(delta_time);
	//Ž©—R—Ž‰º
	free_fall(delta_time);
	//’nŒ`‚ÆÕ“Ë”»’è
	collide_field();
	//’e‚ð”­ŽË
	shoot(delta_time);
}

void Enemy::draw() const
{
	//ƒƒbƒVƒ…‚Ì•`‰æ
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(mesh_);
	glPopMatrix();

	//ForDebug
	//‹«ŠE‹…‚Ì•`‰æ
	collider().draw();
	BoundingSphere{ CannonRange, transform_.position()}.draw();
}

void Enemy::react(Actor& other)
{
	//Ž©‹@’e‚É“–‚½‚Á‚½‚çŽ€–S
	if (other.tag() == "PlayerCannonBallTag") {
		die();
	}
}

void Enemy::move(float delta_time)
{
	//ˆÚ“®—Ê‚ð”½‰f
	transform_.translate(velocity_, GStransform::Space::World);
}

//’…’eˆÊ’u‚ðŽZo‚µA–CŠÛƒNƒ‰ƒX‚É“n‚µ‚Ä¶¬
void Enemy::shoot(float delta_time)
{
	//ˆê’èŽžŠÔ‚²‚Æ‚É’e‚ð”­ŽË
	shot_timer_ += delta_time;
	if (shot_timer_ >= ShotInterval) {
		//ƒvƒŒƒCƒ„[‚ðŽæ“¾
		Actor* player = world_->find_actor("Player");
		//Œ©‚Â‚©‚ç‚È‚©‚Á‚½‚çI—¹
		if (!player) return;
		//’e¶¬ˆÊ’u
		GSvector3 position = transform_.position() + CannonOffset;
		//ƒvƒŒƒCƒ„[•ûŒü‚ðŒvŽZ
		GSvector3 direction = player->transform().position() - transform_.position();
		direction.y = 0.0f;
		//ŽË’ö”ÍˆÍ‚ð§ŒÀ‚µ‚È‚ª‚çA’e’…’eˆÊ’u‚ðŽZo
		GSvector3 destination = transform_.position() + GSvector3::clampMagnitude(direction, CannonRange);
		//’e‚ð¶¬
		world_->add_actor(new CannonBall{ world_, position, destination, "EnemyCannonBallTag" });
		shot_timer_ -= ShotInterval;
	}
}

void Enemy::react_wall()
{
}

/*ˆÈ‰º‚Í‘‚«Š·‚¦‚È‚¢*/
void Enemy::free_fall(float delta_time)
{
	//d—Í‚ðì—p
	velocity_.y += Gravity * delta_time;
	//ã‰º•ûŒü‚ÌˆÚ“®—Ê‚ð”½‰f
	transform_.translate(GSvector3{ 0.0f, velocity_.y * delta_time, 0.0f }, GStransform::Space::World);
}

void Enemy::collide_field()
{
	//’nŒ`‚Æ‚ÌˆÊ’u•â³
	//’n–Ê‚Æ‚ÌÕ“Ë”»’è
	Line line{ collider().center(),  transform_.position() + GSvector3{ 0.0f, -FootOffset, 0.0f } };
	GSvector3 intersect;
	//Õ“Ë‚µ‚½‚ç‚’¼•ûŒü‚É‰Ÿ‚µ–ß‚µ
	if (world_->stage().collide(line, &intersect)) {
		GSvector3 position = line.start();
		position.y = intersect.y - FootOffset;
		transform_.position(position);
		velocity_.y = 0.0f;
	}
	//•Ç‚Æ‚ÌÕ“Ë”»’è
	GSvector3 center;
	//Õ“Ë‚µ‚½‚ç…•½•ûŒü‚É‰Ÿ‚µ–ß‚µ
	if (world_->stage().collide(collider(), &center)) {
		//y‚Í‚»‚Ì‚Ü‚Ü
		center.y = transform_.position().y;
		transform_.position(center);
		react_wall();
	}
}
