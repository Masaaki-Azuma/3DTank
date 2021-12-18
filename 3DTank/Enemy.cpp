#include "Enemy.h"
#include "IWorld.h"
#include "Stage.h"
#include "Line.h"
#include "CannonBall.h"
#include "Assets.h"

//const float MoveSpeed{ 0.2f };                     //ˆÚ“®‘¬‚³
const float Gravity{ -0.02f };                     //d—Í‰Á‘¬“x
const float EnemyHeight{ 2.0f };                   //‹«ŠE‹…’†S‚Ì‚‚³
const float FootOffset{ 0.1f };                    //’n–Ê‚Æ‚Ì“–‚½‚è”»’è—p‚Ì‘«Œ³ƒIƒtƒZƒbƒg
const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };  //’e‚ðŒ‚‚ÂˆÊ’u‚ÌƒIƒtƒZƒbƒg
//const float ShotInterval{ 90.0f };                 //’e‚Ì”­ŽËŠÔŠu
//const float CannonRange{ 16.0f };                  //’e‚ª“Í‚­‹——£

Enemy::Enemy(IWorld* world, const GSvector3& position):
	mesh_{Mesh_Enemy}
{
	world_ = world;
	name_ = "Enemy";
	tag_ = "EnemyTag";
	transform_.position(position);
	//velocity_ = GSvector3{ 0.0f, 0.0f, -MoveSpeed };
	//collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
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
