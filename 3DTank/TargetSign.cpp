#include "TargetSign.h"
#include "IWorld.h"
#include "Assets.h"

const float MoveSpeed{ 0.5f };     //�ړ�����
const float Height{ 0.9f };        //��荂���A�����艺����ƒn�`�ɖ��܂�
const float RangeRadius{ 16.0f };  //�v���C���[���痣�����ő勗��

TargetSign::TargetSign(IWorld* world, const GSvector3& position, const Actor& owner):
	offset_{GSvector3::zero()},
	owner_{owner}
{
	world_ = world;
	name_ = "TargetSign";
	tag_ = "TargetSignTag";
	//y���W���
	transform_.position(GSvector3{ position.x, Height, position.z });
}

void TargetSign::update(float delta_time)
{
	GSvector3 owner_position = owner_.transform().position();
	owner_position.y = Height;
	//�ړ��������Z�o
	GSvector3 direction{ 0.0f, 0.0f, 0.0f };
	if (gsGetKeyState(GKEY_UP)) {
		direction.z -= 1.0f;
	}
	if (gsGetKeyState(GKEY_DOWN)) {
		direction.z += 1.0f;
	}
	if (gsGetKeyState(GKEY_RIGHT)) {
		direction.x += 1.0f;
	}
	if (gsGetKeyState(GKEY_LEFT)) {
		direction.x -= 1.0f;
	}
	//�ړ��ʂ��Z�o
	GSvector3 velocity = direction.normalized() * MoveSpeed * delta_time;
	//�㉺�����ɂ͓������Ȃ�
	velocity.y = 0.0f;
	//�ړ��ʕ����΍��W��ω�
	offset_ += velocity;
	//�v���C���[����̑��΋����𐧌�
	offset_ = GSvector3::clampMagnitude(offset_, RangeRadius);
	//�v���C���[���瑊�Έړ��������W�ֈړ�
	transform_.position(owner_position + offset_);
}

void TargetSign::draw() const
{
	//���b�V���̕`��
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(Mesh_TargetSign);
	glPopMatrix();
}
