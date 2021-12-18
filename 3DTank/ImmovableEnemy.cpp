#include "ImmovableEnemy.h"
#include "IWorld.h"
#include "CannonBall.h"
#include "Assets.h"

const float MoveSpeed{ 0.2f };    //ˆÚ“®‘¬‚³
const float EnemyHeight{ 2.0f };  //‹«ŠE‹…’†S‚Ì‚‚³
const float ShotInterval{ 90.0f };                 //’e‚Ì”­ŽËŠÔŠu
const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };  //’e‚ðŒ‚‚ÂˆÊ’u‚ÌƒIƒtƒZƒbƒg
const float CannonRange{ 16.0f };                  //’e‚ª“Í‚­‹——£

ImmovableEnemy::ImmovableEnemy(IWorld* world, const GSvector3& position):
	Enemy{world, position}
{
	name_ = "ImmovableEnemy";
	tag_ = "EnemyTag";
	velocity_ = GSvector3{ 0.0f, 0.0f, 0.0f };
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
	mesh_ = Mesh_Enemy;
}

void ImmovableEnemy::shoot(float delta_time)
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

