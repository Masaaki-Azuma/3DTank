#ifndef ACTOR_GANERATOR_H_
#define ACTOR_GANERATOR_H_

#include "CsvReader.h"

class IWorld;

//�X�e�[�W�������ƂɃA�N�^�[�Q�𐶐�����N���X
class ActorGenerator
{
public:
	ActorGenerator(IWorld* world);
	//�A�N�^�[�𐶐�
	void generate(unsigned int stage);

private:
	IWorld* world_;
	CsvReader actor_generate_table_;
};
#endif//!ACTOR_GANERATOR_H_

