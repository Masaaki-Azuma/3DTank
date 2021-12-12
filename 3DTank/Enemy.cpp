#include "Enemy.h"
#include "IWorld.h"
#include "Field.h"
#include "Line.h"
#include "CannonBall.h"
#include "Assets.h"

const float MoveSpeed{ 0.2f };
const float Gravity{ -0.05f };
const float EnemyHeight{ 2.0f };
const float FootOffset{ 0.1f };
const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };
const float CannonSpeed{ 0.2f };

Enemy::Enemy(IWorld* world, const GSvector3& position)
{
	world_ = world;
	name_ = "Enemy";
	tag_ = "EnemyTag";
	transform_.position(position);
	velocity_ = GSvector3{ 0.0f, 0.0f, -MoveSpeed };
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
}

void Enemy::update(float delta_time)
{
	//ˆÚ“®
	move(delta_time);
	//Ž©—R—Ž‰º
	free_fall(delta_time);
	//’e‚ð”­ŽË
	shoot(delta_time);
	//’nŒ`‚ÆÕ“Ë”»’è
	collide_field();
}

void Enemy::draw() const
{
	//ƒƒbƒVƒ…‚Ì•`‰æ
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(Mesh_Enemy);
	glPopMatrix();

	//ForDebug
	//‹«ŠE‹…‚Ì•`‰æ
	collider().draw();
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
	//transform_.translate(velocity_, GStransform::Space::World);
}

void Enemy::free_fall(float delta_time)
{
	//d—Í‚ðì—p
	velocity_.y += Gravity * delta_time;
	//ã‰º•ûŒü‚ÌˆÚ“®—Ê‚ð”½‰f
	transform_.translate(GSvector3{ 0.0f, velocity_.y, 0.0f }, GStransform::Space::World);
}

void Enemy::shoot(float delta_time)
{
	//ForDebug
	//ˆê’èŽžŠÔ‚²‚Æ‚É’e‚ð”­ŽË
	shot_timer_ += delta_time;
	if (shot_timer_ >= 60.0f) {
		//ƒvƒŒƒCƒ„[‚ðŽæ“¾
		Actor* player = world_->find_actor("Player");
		//Œ©‚Â‚©‚ç‚È‚©‚Á‚½‚çI—¹
		if (!player) return;
		//ƒvƒŒƒCƒ„[•ûŒü‚ðŒvŽZ
		GSvector3 direction = player->transform().position() - transform_.position();
		//y¬•ª‚Í–³Ž‹
		direction.y = 0.0f;
		//’e‚ÌˆÚ“®—Ê‚ðŽZo
		GSvector3 velocity = direction.normalized() * CannonSpeed;
		//y¬•ª‚Íˆê’è
		velocity.y = 0.8f;
		//’e‚ð¶¬
		world_->add_actor(new CannonBall{ world_, transform_.position() + CannonOffset, velocity, "EnemyCannonBallTag"});
		shot_timer_ -= 60.0f;
	}
	//!ForDebug
}

void Enemy::collide_field()
{
	//’nŒ`‚Æ‚ÌˆÊ’u•â³
	//’n–Ê‚Æ‚ÌÕ“Ë”»’è
	Line line{ collider().center(),  transform_.position() + GSvector3{ 0.0f, -FootOffset, 0.0f } };
	GSvector3 intersect;
	//Õ“Ë‚µ‚½‚ç‚’¼•ûŒü‚É‰Ÿ‚µ–ß‚µ
	if (world_->field().collide(line, &intersect)) {
		GSvector3 position = line.start();
		position.y = intersect.y - FootOffset;
		transform_.position(position);
		velocity_.y = 0.0f;
	}
	//•Ç‚Æ‚ÌÕ“Ë”»’è
	GSvector3 center;
	//Õ“Ë‚µ‚½‚ç…•½•ûŒü‚É‰Ÿ‚µ–ß‚µ
	if (world_->field().collide(collider(), &center)) {
		//y‚Í‚»‚Ì‚Ü‚Ü
		center.y = transform_.position().y;
		transform_.position(center);
		//ˆÚ“®—Ê”½“]
		velocity_.z = -velocity_.z;
	}
}
