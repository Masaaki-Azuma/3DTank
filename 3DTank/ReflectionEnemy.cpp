#include "ReflectionEnemy.h"
#include "IWorld.h"
#include "CannonBall.h"
#include "Assets.h"

const float MoveSpeed{ 0.2f };    //�ړ�����
const float EnemyHeight{ 2.0f };  //���E�����S�̍���
//const float ShotInterval{ 90.0f };                 //�e�̔��ˊԊu
//const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };  //�e�����ʒu�̃I�t�Z�b�g
//const float CannonRange{ 16.0f };                  //�e���͂�����

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
	//�ړ��ʔ��]
	velocity_.z = -velocity_.z;
}
