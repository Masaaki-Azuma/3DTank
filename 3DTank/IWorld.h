#ifndef IWORLD_H_
#define IWORLD_H_

class Actor;

//���[���h���ۃC���^�[�t�F�[�X
class IWorld
{
public:
	//�A�N�^�[�̒ǉ�
	virtual void add_actor(Actor* actor) = 0;
};

#endif//!IWORLD_H_
