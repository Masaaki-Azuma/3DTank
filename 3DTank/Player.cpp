#include "Player.h"
#include "CannonBall.h"
#include "IWorld.h"
#include "Line.h"
#include "Field.h"
#include "Assets.h"

const float MoveSpeed{ 0.2f };
const float Gravity{ -0.05f };
const float PlayerHeight{ 2.0f };
const float FootOffset{ 0.1f };
const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };

Player::Player(IWorld* world, const GSvector3& position)
{
	world_ = world;
	name_ = "Player";
	tag_ = "PlayerTag";
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, 2.0f, 0.0f} };
	transform_.position(position);
}

void Player::update(float delta_time)
{
	//�ړ�
	move(delta_time);
	//�d�͂ɂ�鎩�R����
	free_fall(delta_time);
	//�C�ۂ̔���
	shoot();
	//�n�`�ƏՓ˔���
	collide_field();
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
	GSvector3 velocity = direction.normalized() * MoveSpeed * delta_time;
	//x,z�������̈ړ��ʂ�ۑ�
	velocity_.x = velocity.x;
	velocity_.z = velocity.z;
	//���������̈ړ��ʂ𔽉f
	transform_.translate(velocity, GStransform::Space::World);
}

void Player::free_fall(float delta_time)
{
	//�d�͂���p
	velocity_.y += Gravity * delta_time;
	//�㉺�����̈ړ��ʂ𔽉f
	transform_.translate(GSvector3{ 0.0f, velocity_.y, 0.0f }, GStransform::Space::World);
}

void Player::shoot()
{
	//�e�𔭎�
	if (gsGetKeyTrigger(GKEY_SPACE)) {
		//�e�̕���
		GSvector3 direction{ 0.0f, 0.0f, 0.0f };
		if (gsGetKeyState(GKEY_RIGHT)) {
			direction.x += 1.0f;
		}
		if (gsGetKeyState(GKEY_LEFT)) {
			direction.x -= 1.0f;
		}
		if (gsGetKeyState(GKEY_UP)) {
			direction.z -= 1.0f;
		}
		if (gsGetKeyState(GKEY_DOWN)) {
			direction.z += 1.0f;
		}
		//�e�̑��x
		GSvector3 velocity = direction.normalized() * 0.2;
		//�㉺�����̈ړ��ʂ͌Œ�
		velocity.y = 0.8f;
		//�C�ۂ𔭎�
		world_->add_actor(new CannonBall{ world_, transform_.position() + CannonOffset, velocity, "PlayerCannonBallTag" });
	}
}

void Player::collide_field()
{
	//�n�`�Ƃ̈ʒu�␳

	//�n�ʂƂ̏Փ˔���
	Line line{ collider().center(),  transform_.position() + GSvector3{ 0.0f, -FootOffset, 0.0f } };
	GSvector3 intersect;
	//�Փ˂����琂�������ɉ����߂�
	if (world_->field().collide(line, &intersect)) {
		GSvector3 position = line.start();
		position.y = intersect.y - FootOffset;
		transform_.position(position);
		velocity_.y = 0.0f;
	}
	//�ǂƂ̏Փ˔���
	GSvector3 center;
	//�Փ˂����琅�������ɉ����߂�
	if (world_->field().collide(collider(), &center)) {
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
	//�����o����̈ʒu
	GSvector3 position = other.transform().position() + direction.normalized() * length;
	//�v�Z�l���ړ�
	transform_.position(position);
}
