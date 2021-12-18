#ifndef IWORLD_H_
#define IWORLD_H_

#include <string>

class Actor;
class Stage;

//���[���h���ۃC���^�[�t�F�[�X
class IWorld
{
public:
	//�A�N�^�[�̒ǉ�
	virtual void add_actor(Actor* actor) = 0;
	//�A�N�^�[�̖��O����
	virtual Actor* find_actor(const std::string& name) const = 0;
	//�A�N�^�[�̃^�O����
	virtual Actor* find_actor_with_tag(const std::string& name) const = 0;
	//�A�N�^�[�̑S�폜
	virtual void clear_actor() = 0;
	//���x���N���A��Ԃ��H
	virtual bool is_level_clear() const = 0;

	//�X�e�[�W�̎擾
	virtual Stage& stage() = 0;
};

#endif//!IWORLD_H_
