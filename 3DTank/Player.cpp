#include "Player.h"
#include "CannonBall.h"
#include "PlayerCannonBall.h"
#include "TargetSign.h"
#include "IWorld.h"
#include "Line.h"
#include "Stage.h"
#include "Assets.h"

const float MoveSpeed{ 0.2f };
const float Gravity{ -0.02f };
const float PlayerHeight{ 2.0f };
const float FootOffset{ 0.1f };
const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };
const float CannonVerticalSpeed{ 0.8f };  //�e�̉��������x
const float CannonVelocityFactor{ -2 * CannonVerticalSpeed / Gravity };  //�e�̐������x�����肷��W���A= -2*CannonVerticalSpeed/CannonBall::Gravity


Player::Player(IWorld* world, const GSvector3& position)
{
	world_ = world;
	name_ = "Player";
	tag_ = "PlayerTag";
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, PlayerHeight, 0.0f} };
	transform_.position(position);
	world_->add_actor(new TargetSign{ world_, position, *this });
}

void Player::update(float delta_time)
{
	//�N���A��ԂȂ�ړ��𑀍���֎~
	if (world_->is_level_clear()) return;
	//�ړ�
	move(delta_time);
	//�d�͂ɂ�鎩�R����
	free_fall(delta_time);
	//�n�`�ƏՓ˔���
	collide_field();
	//�C�ۂ̔���
	shoot();
}

void Player::draw() const
{
	//���b�V���̕`��
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(Mesh_Player);
	glPopMatrix();

	//ForDebug
	//���E���̕`��
	collider().draw();
}

void Player::react(Actor& other)
{
	//�N���A��ԂȂ玀�S���Ȃ�
	if (world_->is_level_clear()) return;

	//�G�e�ɓ��������玀�S
	if (other.tag() == "EnemyCannonBallTag") {
		die();
	}
	if (other.tag() == "EnemyTag") {
		//�����o������
		collide_actor(other);
	}
}

void Player::move(float delta_time)
{
	//�ړ�����
	GSvector3 direction{ 0.0f, 0.0f, 0.0f };
	//WASD����ňړ�
	if (gsGetKeyState(GKEY_D)) {
		direction.x += 1.0f;
	}
	if (gsGetKeyState(GKEY_A)) {
		direction.x -= 1.0f;
	}
	if (gsGetKeyState(GKEY_W)) {
		direction.z -= 1.0f;
	}
	if (gsGetKeyState(GKEY_S)) {
		direction.z += 1.0f;
	}
	//�ړ��ʂ̎Z�o
	GSvector3 velocity = direction.normalized() * MoveSpeed;
	//x,z�������̈ړ��ʂ�ۑ�
	velocity_.x = velocity.x;
	velocity_.z = velocity.z;
	//���������̈ړ��ʂ𔽉f
	transform_.translate(velocity * delta_time, GStransform::Space::World);
}

void Player::free_fall(float delta_time)
{
	//�d�͂���p
	velocity_.y += Gravity * delta_time;
	//�㉺�����̈ړ��ʂ𔽉f
	transform_.translate(GSvector3{ 0.0f, velocity_.y * delta_time, 0.0f }, GStransform::Space::World);
}

//���e�ʒu��C�ۃN���X�ɓn���Đ���
void Player::shoot()
{
	if (gsGetKeyTrigger(GKEY_SPACE)) {
		Actor* target = world_->find_actor("TargetSign");
		if (!target) return;
		//�e���e�ʒu
		GSvector3 destination = target->transform().position();
		//�e�����ʒu
		GSvector3 position = transform_.position() + CannonOffset;
		//�e�𐶐�
		world_->add_actor(new PlayerCannonBall{
			world_, position, destination});
	}
}

void Player::collide_field()
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
		center.y = transform_.position().y;
		transform_.position(center);
	}
}

void Player::collide_actor(Actor& other)
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
