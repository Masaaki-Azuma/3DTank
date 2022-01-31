#include "PredictionEnemy.h"
#include "PlayScene/IWorld.h"
#include "Assets.h"

enum
{
	Walk,
	Run,
};

const float EnemyHeight{ 2.0f };  //���E�����S�̍���
const float MoveSpeed{ 0.1f };    //�ړ�����
const float MaxRunTimer{ 180.0f }; //�ǐՎ���
const float MaxWalkTimer{ 300.0f }; //���S����


PredictionEnemy::PredictionEnemy(IWorld* world, const GSvector3& position):
	Enemy{world, position, 90.0f, 30.0f},
	move_timer_{MaxWalkTimer},
	move_state_{Walk}
{
	name_ = "PredictionEnemy";
	tag_ = "EnemyTag";
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
	mesh_ = Mesh_PredictionEnemy;
}

//�v���C���[���瓦����
void PredictionEnemy::move(float delta_time)
{
	//�^�C�}�[�X�V
	update_timer(delta_time);
	//���S�^�C�}�[���c���Ă���Ȃ�A���S��Ԃ𑱂���
	switch (move_state_) {
	case Walk: move_walk(delta_time); break;
	case Run: move_run(delta_time); break;
	}
}

void PredictionEnemy::shoot(float delta_time)
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
		//���ː�i�˓I�����␳�O�j
		//TODO:�C�ۃN���X�̒萔���ǂ��ɂ��擾����
		GSvector3 destination = player->transform().position() + player->velocity() * 80.0f;
		//���˕����i�˓I�����␳�O�j
		GSvector3 direction = destination - transform_.position();
		direction.y = 0.0f;
		//���˕����i�˓I�����␳��j
		direction = GSvector3::clampMagnitude(direction, CannonRange);
		//���ː�i�˓I�����␳��j
		destination = position + direction;
		//�e�𐶐�
		generate_cannon_ball(position, destination);
		shot_timer_ -= ShotInterval;
	}
}

void PredictionEnemy::move_walk(float delta_time)
{
	//�v���C���[������
	Actor* player = world_->find_actor("Player");
	if (!player) return;

	//�v���C���[���玩���֌������������擾
	GSvector3 direction = transform_.position() - player->transform().position();
	direction.y = 0.0f;
	//�ő呬�x�𐧌�
	direction = GSvector3::clampMagnitude(direction, MoveSpeed);
	//���ݑ��x�����������擾
	GSvector3 velocity{ velocity_.x, 0.0f, velocity_.z };
	//�ڕW���x�ƌ��ݑ��x����
	velocity = GSvector3::slerp(direction, velocity, 0.05f);
	//�ړ��ʂ𔽉f
	transform_.translate(velocity * delta_time);
	//�����o�ɐ��������ړ��ʂ��L�[�v
	velocity_.x = velocity.x;
	velocity_.z = velocity.z;
}

void PredictionEnemy::move_run(float delta_time)
{
	//�v���C���[������
	Actor* player = world_->find_actor("Player");
	if (!player) return;

	//�v���C���[�������擾
	GSvector3 direction = player->transform().position() - transform_.position();
	direction.y = 0.0f;
	//�ő呬�x�𐧌�
	direction = GSvector3::clampMagnitude(direction, MoveSpeed * 1.2f);
	//���ݑ��x�����������擾
	GSvector3 velocity{ velocity_.x, 0.0f, velocity_.z };
	//�ڕW���x�ƌ��ݑ��x����
	velocity = GSvector3::slerp(direction, velocity, 0.05f);
	//�ړ��ʂ𔽉f
	transform_.translate(velocity * delta_time);
	//�����o�ɐ��������ړ��ʂ��L�[�v
	velocity_.x = velocity.x;
	velocity_.z = velocity.z;
}

void PredictionEnemy::update_timer(float delta_time)
{
	move_timer_ -= delta_time;
	//�^�C�}�[�̎c�莞�Ԃ��Ȃ��Ȃ�����ړ���ԕύX
	if (move_timer_ <= 0.0f) {
		if (move_state_ == Walk) {
			move_state_ = Run;
			move_timer_ = MaxRunTimer;
		}
		else if (move_state_ == Run) {
			move_state_ = Walk;
			move_timer_ = MaxWalkTimer;
		}
	}
}
