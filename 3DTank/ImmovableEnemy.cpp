#include "ImmovableEnemy.h"
#include "IWorld.h"
#include "CannonBall.h"
#include "Assets.h"

const float EnemyHeight{ 2.0f };  //���E�����S�̍���
//const float ShotInterval{ 90.0f };                 //�e�̔��ˊԊu
//const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };  //�e�����ʒu�̃I�t�Z�b�g
//const float CannonRange{ 16.0f };                  //�e���͂�����

ImmovableEnemy::ImmovableEnemy(IWorld* world, const GSvector3& position):
	Enemy{world, position, 90.0f, 16.0f}
{
	name_ = "ImmovableEnemy";
	tag_ = "EnemyTag";
	velocity_ = GSvector3{ 0.0f, 0.0f, 0.0f };
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
	mesh_ = Mesh_ImmovableEnemy;
}

