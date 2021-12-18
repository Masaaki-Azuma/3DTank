#ifndef TARGET_SIGN_H_
#define TARGET_SIGN_H_

#include "Actor.h"

//�C�ۂ̒��e�ʒu�������Ə��N���X
class TargetSign : public Actor
{
public:
	TargetSign(IWorld* world, const GSvector3& position);
	void update(float delta_time) override;
	void draw() const override;

private:
	//TODO:�R���X�g���N�^�ŃI�[�i�[�ւ̎Q�Ƃ���������ׂ�
	GSvector3 offset_;  //�Ə��̎����傩��̑��Έʒu
};
#endif//!TARGET_SIGN_H_

