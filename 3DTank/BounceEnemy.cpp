#include "BounceEnemy.h"
#include "IWorld.h"
#include "BounceCannonBall.h"
#include "Assets.h"

const float EnemyHeight{ 2.0f };  //‹«ŠE‹…’†S‚Ì‚‚³

BounceEnemy::BounceEnemy(IWorld* world, const GSvector3& position):
	Enemy{world, position, 120.0f}
{
	name_ = "BounceEnemy";
	tag_ = "EnemyTag";
	velocity_ = GSvector3{ 0.0f, 0.0f, 0.0f };
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
	mesh_ = Mesh_Enemy;
}

void BounceEnemy::generate_cannon_ball(const GSvector3& position, const GSvector3& destination)
{
	world_->add_actor(new BounceCannonBall{ world_, position, destination });
}

