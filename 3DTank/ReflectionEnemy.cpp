#include "ReflectionEnemy.h"
#include "IWorld.h"
#include "CannonBall.h"
#include "Assets.h"

const float MoveSpeed{ 0.2f };    //ˆÚ“®‘¬‚³
const float EnemyHeight{ 2.0f };  //‹«ŠE‹…’†S‚Ì‚‚³
//const float ShotInterval{ 90.0f };                 //’e‚Ì”­ËŠÔŠu
//const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };  //’e‚ğŒ‚‚ÂˆÊ’u‚ÌƒIƒtƒZƒbƒg
//const float CannonRange{ 16.0f };                  //’e‚ª“Í‚­‹——£

ReflectionEnemy::ReflectionEnemy(IWorld* world, const GSvector3& position):
	Enemy{world, position, 90.0f, 16.0f}
{
	name_ = "ReflectionEnemy";
	tag_ = "EnemyTag";
	velocity_ = GSvector3{ 0.0f, 0.0f, MoveSpeed };
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
	mesh_ = Mesh_Enemy;
}

void ReflectionEnemy::react_wall()
{
	//ˆÚ“®—Ê”½“]
	velocity_.z = -velocity_.z;
}
