#ifndef ACTOR_MANGER_H_
#define ACTOR_MANGER_H_

#include <list>
#include <string>

class Actor;

class ActorManager
{
public:
	ActorManager() = default;
	~ActorManager();
	//�S�A�N�^�[�̍X�V
	void update(float delta_time);
	//�S�A�N�^�[�̕`��
	void draw() const;
	//�SGUI�̕`��
	void draw_gui() const;

	//�A�N�^�[�̒ǉ�
	void add(Actor* actor);
	//�S�A�N�^�[���m�̏Փ˔���
	void collide();
	//���S�A�N�^�[�̍폜
	void remove();
	//���O�Ō���
	Actor* find(const std::string& name) const;
	//�^�O�Ō���
	Actor* find_with_tag(const std::string& tag) const;
	void clear();

private:
	std::list<Actor*> actors_;
};
#endif//!ACTOR_MANGER_H_

