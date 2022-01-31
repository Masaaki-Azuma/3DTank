#ifndef TARGET_SIGN_H_
#define TARGET_SIGN_H_

#include "Actor.h"

//�C�ۂ̒��e�ʒu�������Ə��N���X
class TargetSign : public Actor
{
public:
	TargetSign(IWorld* world, const GSvector3& position, const Actor& owner);
	void update(float delta_time) override;
	void draw() const override;
private:
	//�ړ�
	void move(float delta_time);
	//�ʒu��ǂ̒������ɐ���
	void collide_wall(const GSvector3& position);
private:
	GSvector3 offset_;  //�Ə��̎����傩��̑��Έʒu
	const Actor& owner_;
};
#endif//!TARGET_SIGN_H_

