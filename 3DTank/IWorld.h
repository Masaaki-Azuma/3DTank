#ifndef IWORLD_H_
#define IWORLD_H_

#include <string>

class Actor;
class Field;

//���[���h���ۃC���^�[�t�F�[�X
class IWorld
{
public:
	//�A�N�^�[�̒ǉ�
	virtual void add_actor(Actor* actor) = 0;
	//�A�N�^�[�̖��O����
	virtual void find_actor(const std::string& name) const = 0;
	//�A�N�^�[�̃^�O����
	virtual void find_actor_with_tag(const std::string& name) const = 0;

	//�t�B�[���h�̎擾
	virtual Field& field() = 0;
};

#endif//!IWORLD_H_
