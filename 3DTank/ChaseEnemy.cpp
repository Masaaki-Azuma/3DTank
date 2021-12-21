#include "ChaseEnemy.h"
#include "IWorld.h"
#include "Assets.h"

const float EnemyHeight{ 2.0f };  //‹«ŠE‹…’†S‚Ì‚‚³
const float MoveSpeed{ 0.1f };    //ˆÚ“®‘¬‚³


ChaseEnemy::ChaseEnemy(IWorld* world, const GSvector3& position):
	Enemy{world, position}
{
	name_ = "ChaseEnemy";
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
	mesh_ = Mesh_Enemy;

	velocity_ = GSvector3{ 0.0f, 0.0f, 0.0f };
}

void ChaseEnemy::move(float delta_time)
{
	Actor* player = world_->find_actor("Player");
	if (!player) return;

	GSvector3 direction = player->transform().position() - transform_.position();
	direction.y = 0.0f;
	direction = GSvector3::clampMagnitude(direction, MoveSpeed);
	velocity_ = GSvector3::slerp(direction, velocity_, 0.05f);

	transform_.translate(velocity_ * delta_time);
}
