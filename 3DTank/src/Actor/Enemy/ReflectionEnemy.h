#ifndef REFLECTION_ENEMY_H_
#define REFLECTION_ENEMY_H_

#include "Enemy.h"

//�ǂɓ�����Ɣ��˂���G
class ReflectionEnemy : public Enemy
{
public:
	ReflectionEnemy(IWorld* world, const GSvector3& position, float angleY = 0.0f);
protected:
	virtual void move(float delta_time) override;
	//�ǂɏՓˎ��̋���
	virtual void react_wall() override;

private:
	GSvector3 prev_position_;
};
#endif//!REFLECTION_ENEMY_H_

