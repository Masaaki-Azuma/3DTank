#include "BlastMortorEnemy.h"
#include "IWorld.h"
#include "BlastCannonBall.h"
#include "Assets.h"

const float EnemyHeight{ 2.0f };  //���E�����S�̍���

BlastMortorEnemy::BlastMortorEnemy(IWorld* world, const GSvector3& position):
	Enemy{world, position, 180.0f, 30.0f}
{
	name_ = "BlastMortorEnemy";
	tag_ = "EnemyTag";
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
	mesh_ = Mesh_BlastMortorEnemy;
}

void BlastMortorEnemy::move(float delta_time)
{
	//�����Ȃ�
}

void BlastMortorEnemy::generate_cannon_ball(const GSvector3& position, const GSvector3& destination)
{
	//�����C�ۂ𔭎�
	world_->add_actor(new BlastCannonBall{ world_, position, destination });
}
