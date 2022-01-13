#include "TargetSign.h"
#include "IWorld.h"
#include "Stage.h"
#include "Assets.h"

const float MoveSpeed{ 0.5f };     //�ړ�����
const float Height{ 0.9f };        //��荂���A�����艺����ƒn�`�ɖ��܂�
const float RangeRadius{ 16.0f };  //�v���C���[���痣�����ő勗��
const GSrect Size{ -2,-2, 2, 2 };
const GSrect StageSize{ -33,-20.5f, 33, 20.5 };

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
	move(delta_time);
}

void TargetSign::draw() const
{
	//���b�V���̕`��
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(Mesh_TargetSign);
	glPopMatrix();
}

void TargetSign::move(float delta_time)
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
	//�ǂɂ�鉟���o���O�̃��[���h���W���Z�o
	GSvector3 position = owner_position + offset_;
	//�ǂ̓����ɐ���
	collide_wall(position);
	//�ǂɂ�鉟���o����̃��[���h���W���Z�o
	position = owner_position + offset_;
	//�v���C���[���瑊�Έړ��������W�ֈړ�
	transform_.position(position);
}

void TargetSign::collide_wall(const GSvector3& position)
{
	//�X�e�[�W�O�g�ƏƏ��̑傫�����狁�܂�A�ʒu�̌��E�l
	static const float left_limit{ StageSize.left - Size.left };
	static const float right_limit{ StageSize.right - Size.right };
	static const float top_limit{ StageSize.top - Size.top };
	static const float bottom_limit{ StageSize.bottom - Size.bottom };
	//�ǂɖ��܂��������Ԃ�A�I�t�Z�b�g�������߂�
	if (position.x < left_limit) {
		offset_.x += left_limit - position.x;
	}
	else if (position.x > right_limit) {
		offset_.x += right_limit - position.x;
	}

	if (position.z < top_limit) {
		offset_.z += top_limit - position.z;
	}
	else if (position.z > bottom_limit) {
		offset_.z += bottom_limit - position.z;
	}
}

//HACK:collide_field��Actor�ł܂Ƃ߂�ׂ��ł́H(virtual�ŃI�[�o�[���C�h�ł���悤�ɂ��Ă���)
