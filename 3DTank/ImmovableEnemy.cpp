#include "ImmovableEnemy.h"
#include "IWorld.h"
#include "CannonBall.h"
#include "Assets.h"

const float MoveSpeed{ 0.2f };    //�ړ�����
const float EnemyHeight{ 2.0f };  //���E�����S�̍���
const float ShotInterval{ 90.0f };                 //�e�̔��ˊԊu
const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };  //�e�����ʒu�̃I�t�Z�b�g
const float CannonRange{ 16.0f };                  //�e���͂�����

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
	//��莞�Ԃ��Ƃɒe�𔭎�
	shot_timer_ += delta_time;
	if (shot_timer_ >= ShotInterval) {
		//�v���C���[���擾
		Actor* player = world_->find_actor("Player");
		//������Ȃ�������I��
		if (!player) return;
		//�e�����ʒu
		GSvector3 position = transform_.position() + CannonOffset;
		//�v���C���[�������v�Z
		GSvector3 direction = player->transform().position() - transform_.position();
		direction.y = 0.0f;
		//�˒��͈͂𐧌����Ȃ���A�e���e�ʒu���Z�o
		GSvector3 destination = transform_.position() + GSvector3::clampMagnitude(direction, CannonRange);
		//�e�𐶐�
		world_->add_actor(new CannonBall{ world_, position, destination, "EnemyCannonBallTag" });
		shot_timer_ -= ShotInterval;
	}
}

