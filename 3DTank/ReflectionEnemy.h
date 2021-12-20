#ifndef REFLECTION_ENEMY_H_
#define REFLECTION_ENEMY_H_

#include "Enemy.h"

//�ǂɓ�����Ɣ��˂���G
class ReflectionEnemy : public Enemy
{
public:
	ReflectionEnemy(IWorld* world, const GSvector3& position);
private:
	//�ǂɏՓˎ��̋���
	virtual void react_wall() override;
};
#endif//!REFLECTION_ENEMY_H_

