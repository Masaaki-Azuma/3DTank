#include "CannonBall.h"
#include <GSeffect.h>
#include "PlayScene/IWorld.h"
#include "PlayScene/Stage.h"
#include "Assets.h"

//const float Gravity{ -0.02f };
//const float CannonVerticalSpeed{ 0.8f };  //�e�̉��������x
//const float CannonVelocityFactor{ -2 * CannonVerticalSpeed / Gravity };  //�e�̐������x�����肷��W���A= -2*CannonVerticalSpeed/CannonBall::Gravity

CannonBall::CannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination):
	mesh_{ Mesh_CannonBall }
{
	world_ = world;
	transform_.position(position);
	collider_ = BoundingSphere{ 1.0f };
}

void CannonBall::update(float delta_time)
{
	//�ړ�
	move(delta_time);
	//�n�`�Ƃ̏Փˏ���
	collide_field();
}

void CannonBall::draw() const
{
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(mesh_);
	glPopMatrix();

	//ForDebug
	//collider().draw();
}

void CannonBall::react(Actor& other)
{
	
}
//HACK:�����炭�h���N���X�ł����������ɂȂ邪�AGravity�萔���ǂ��ɂ����Ĉ�{�ɂ܂Ƃ߂��Ȃ����낤���H
void CannonBall::move(float delta_time)
{
	
}

void CannonBall::collide_field()
{
	//�n�`�ɓ���������폜
	if (world_->stage().collide(collider())) {
		GSvector3 position = transform_.position();
		gsPlayEffect(Effect_Smoke, &position);
		die();
	}
}
