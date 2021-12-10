#include "Player.h"
#include "CannonBall.h"
#include "IWorld.h"

const float MoveSpeed{ 0.2f };
Player::Player(IWorld* world, const GSvector3& position):
	world_{world}
{
	collider_ = BoundingSphere{ 2.0f, GSvector3{0.0f, 1.0f, 0.0f} };
	transform_.position(position);
}

void Player::update(float delta_time)
{
	//�ړ�
	move(delta_time);
	//�C�ۂ̔���
	shoot();
}

void Player::draw() const
{
	//���b�V���̕`��
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(0);
	glPopMatrix();

	//ForDebug
	//���E���̕`��
	collider().draw();
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
	//�ړ��ʂ𔽉f
	transform_.translate(velocity, GStransform::Space::World);
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
		world_->add_actor(new CannonBall{ transform_.position(), velocity});
	}
}
