#include "MortorEnemy.h"
#include "Assets.h"

const float EnemyHeight{ 2.0f };  //‹«ŠE‹…’†S‚Ì‚‚³

MortorEnemy::MortorEnemy(IWorld* world, const GSvector3& position):
	Enemy{world, position, 120.0f, 30.0f}
{
	name_ = "MortorEnemy";
	tag_ = "EnemyTag";
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
	mesh_ = Mesh_MortorEnemy;
}

void MortorEnemy::move(float delta_time)
{
}
