#include "ChaseEnemy.h"
#include "IWorld.h"
#include "Assets.h"

const float EnemyHeight{ 2.0f };  //���E�����S�̍���
const float MoveSpeed{ 0.1f };    //�ړ�����


ChaseEnemy::ChaseEnemy(IWorld* world, const GSvector3& position):
	Enemy{world, position}
{
	name_ = "ChaseEnemy";
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
	mesh_ = Mesh_ChaseEnemy;

	velocity_ = GSvector3{ 0.0f, 0.0f, 0.0f };
}

void ChaseEnemy::move(float delta_time)
{
	//�v���C���[������
	Actor* player = world_->find_actor("Player");
	if (!player) return;

	//�v���C���[�������擾
	GSvector3 direction = player->transform().position() - transform_.position();
	direction.y = 0.0f;
	//�ő呬�x�𐧌�
	direction = GSvector3::clampMagnitude(direction, MoveSpeed);
	//���ݑ��x�����������擾
	GSvector3 velocity{ velocity_.x, 0.0f, velocity_.z };
	//�ڕW���x�ƌ��ݑ��x����
	velocity = GSvector3::slerp(direction, velocity, 0.05f);
	//�ړ��ʂ𔽉f
	transform_.translate(velocity * delta_time);
}
