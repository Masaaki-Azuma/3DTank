#include "ReflectionEnemy.h"
#include "IWorld.h"
#include "CannonBall.h"
#include "Assets.h"

const float MoveSpeed{ 0.15f };    //�ړ�����
const float EnemyHeight{ 2.0f };  //���E�����S�̍���
//const float ShotInterval{ 90.0f };                 //�e�̔��ˊԊu
//const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };  //�e�����ʒu�̃I�t�Z�b�g
//const float CannonRange{ 16.0f };                  //�e���͂�����

ReflectionEnemy::ReflectionEnemy(IWorld* world, const GSvector3& position, float angleY):
	Enemy{world, position, 100.0f, 16.0f},
	prev_position_{position}
{
	name_ = "ReflectionEnemy";
	tag_ = "EnemyTag";
	velocity_ = GSvector3{ MoveSpeed, 0.0f, 0.0f };
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
	mesh_ = Mesh_ReflectionEnemy;
	transform_.rotate(GSvector3{ 0.0f, angleY, 0.0f });
}

void ReflectionEnemy::move(float delta_time)
{
	//���[�J�����W��ňړ�
	transform_.translate(velocity_);
}

void ReflectionEnemy::react_wall()
{
	float diffrence = (transform_.position() - prev_position_).length();
	//�ړ��������Z��������A�Փ˂Ɣ��f���Ĉړ��ʂ𔽓]
	if (diffrence < 0.05) {
		//�ړ��ʔ��]
		velocity_ = -velocity_;
	}
	prev_position_ = transform_.position();
}
