#include "Enemy.h"
#include "IWorld.h"
#include "Stage.h"
#include "Line.h"
//#include "CannonBall.h"
#include "CommonCannonBall.h"
#include "Assets.h"

const float Gravity{ -0.02f };                     //�d�͉����x
//const float EnemyHeight{ 2.0f };                   //���E�����S�̍���
const float FootOffset{ 0.1f };                    //�n�ʂƂ̓����蔻��p�̑����I�t�Z�b�g
//const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };  //�e�����ʒu�̃I�t�Z�b�g

Enemy::Enemy(IWorld* world, const GSvector3& position, float shot_inteval, float cannon_range):
	mesh_{Mesh_Enemy},
	ShotInterval{shot_inteval},
	CannonRange{cannon_range}
{
	world_ = world;
	name_ = "Enemy";
	tag_ = "EnemyTag";
	transform_.position(position);
}

void Enemy::update(float delta_time)
{
	//�ړ�
	move(delta_time);
	//���R����
	free_fall(delta_time);
	//�n�`�ƏՓ˔���
	collide_field();
	//�e�𔭎�
	shoot(delta_time);
}

void Enemy::draw() const
{
	//���b�V���̕`��
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(mesh_);
	glPopMatrix();

	//ForDebug
	//���E���̕`��
	collider().draw();
	BoundingSphere{ CannonRange, transform_.position()}.draw();
}

void Enemy::react(Actor& other)
{
	//���@�e�ɓ��������玀�S
	if (other.tag() == "PlayerCannonBallTag") {
		die();
	}
	else if(other.tag() == "PlayerTag" || other.tag() == "EnemyTag"){
		collide_actor(other);
	}

}

void Enemy::move(float delta_time)
{
	//�ړ��ʂ𔽉f
	transform_.translate(velocity_, GStransform::Space::World);
}

//���e�ʒu���Z�o���A�C�ۃN���X�ɓn���Đ���
void Enemy::shoot(float delta_time)
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
		generate_cannon_ball(position, destination);
		shot_timer_ -= ShotInterval;
	}
}

void Enemy::generate_cannon_ball(const GSvector3& position, const GSvector3& destination)
{
	world_->add_actor(new CommonCannonBall{ world_, position, destination });
}

void Enemy::react_wall()
{
}

/*�ȉ��͏��������Ȃ�*/
void Enemy::free_fall(float delta_time)
{
	//�d�͂���p
	velocity_.y += Gravity * delta_time;
	//�㉺�����̈ړ��ʂ𔽉f
	transform_.translate(GSvector3{ 0.0f, velocity_.y * delta_time, 0.0f }, GStransform::Space::World);
}

void Enemy::collide_field()
{
	//�n�`�Ƃ̈ʒu�␳
	//�n�ʂƂ̏Փ˔���
	Line line{ collider().center(),  transform_.position() + GSvector3{ 0.0f, -FootOffset, 0.0f } };
	GSvector3 intersect;
	//�Փ˂����琂�������ɉ����߂�
	if (world_->stage().collide(line, &intersect)) {
		GSvector3 position = line.start();
		position.y = intersect.y - FootOffset;
		transform_.position(position);
		velocity_.y = 0.0f;
	}
	//�ǂƂ̏Փ˔���
	GSvector3 center;
	//�Փ˂����琅�������ɉ����߂�
	if (world_->stage().collide(collider(), &center)) {
		//y�͂��̂܂�
		center.y = transform_.position().y;
		transform_.position(center);
		react_wall();
	}
}

void Enemy::collide_actor(Actor& other)
{
	//���肩�玩���֌������x�N�g��
	GSvector3 direction = transform_.position() - other.transform().position();
	direction.y = 0.0f;
	//���ׂ�����
	float length = collider().radius() + other.collider().radius();
	//�d�Ȃ蒷��
	float overlap = length - direction.length();
	//�����o����̈ʒu
	GSvector3 velocity = direction.normalized() * overlap;
	//�v�Z�l���ړ�
	transform_.translate(velocity, GStransform::Space::World);
	//�n�`����͂ݏo�Ȃ��悤�ɍĔ���
	collide_field();
}
