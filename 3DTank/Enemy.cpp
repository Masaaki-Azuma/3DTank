#include "Enemy.h"
#include "IWorld.h"
#include "Stage.h"
#include "Line.h"
#include "CannonBall.h"
#include "Assets.h"

//const float MoveSpeed{ 0.2f };                     //�ړ�����
const float Gravity{ -0.02f };                     //�d�͉����x
const float EnemyHeight{ 2.0f };                   //���E�����S�̍���
const float FootOffset{ 0.1f };                    //�n�ʂƂ̓����蔻��p�̑����I�t�Z�b�g
const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };  //�e�����ʒu�̃I�t�Z�b�g
//const float ShotInterval{ 90.0f };                 //�e�̔��ˊԊu
//const float CannonRange{ 16.0f };                  //�e���͂�����

Enemy::Enemy(IWorld* world, const GSvector3& position):
	mesh_{Mesh_Enemy}
{
	world_ = world;
	name_ = "Enemy";
	tag_ = "EnemyTag";
	transform_.position(position);
	//velocity_ = GSvector3{ 0.0f, 0.0f, -MoveSpeed };
	//collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
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
}

void Enemy::react(Actor& other)
{
	//���@�e�ɓ��������玀�S
	if (other.tag() == "PlayerCannonBallTag") {
		die();
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
