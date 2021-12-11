#ifndef IWORLD_H_
#define IWORLD_H_

class Actor;
class Field;

//���[���h���ۃC���^�[�t�F�[�X
class IWorld
{
public:
	//�A�N�^�[�̒ǉ�
	virtual void add_actor(Actor* actor) = 0;
	//�t�B�[���h�̎擾
	virtual Field& field() = 0;
};

#endif//!IWORLD_H_
