#include "ActorManager.h"
#include "Actor.h"

ActorManager::~ActorManager()
{
	clear();
}

void ActorManager::update(float delta_time)
{
	//�S�A�N�^�[�̍X�V
	for (auto actor : actors_) {
		actor->update(delta_time);
	}
}

void ActorManager::draw() const
{
	//�S�A�N�^�[�̕`��
	for (auto actor : actors_) {
		actor->draw();
	}
}

void ActorManager::draw_gui() const
{
	//�SGUI�̕`��
	for (auto actor : actors_) {
		actor->draw_gui();
	}
}

void ActorManager::add(Actor* actor)
{
	//�A�N�^�[�̒ǉ�
	actors_.push_back(actor);
}

void ActorManager::collide()
{
	//�A�N�^�[���m�̑S�g�ݍ��킹�ŏՓ˔�����s��
	for (auto i = actors_.begin(); i != actors_.end(); ++i) {
		for (auto j = std::next(i); j != actors_.end(); ++j) {
			(*i)->collide(**j);
		}
	}
}

void ActorManager::remove()
{
	//���S���Ă���A�N�^�[���폜����
	for (auto itr = actors_.begin(); itr != actors_.end();) {
		if ((*itr)->is_dead()) {
			delete* itr;
			itr = actors_.erase(itr);
		}
		else {
			++itr;
		}
	}
}

Actor* ActorManager::find(const std::string& name) const
{
	//���O����v�����A�N�^�[��Ԃ�
	for (auto actor : actors_) {
		if (actor->name() == name) {
			return actor;
		}
	}
	//��v���Ȃ������ꍇnullptr��Ԃ�
	return nullptr;
}

Actor* ActorManager::find_with_tag(const std::string& tag) const
{
	//�^�O����v�����A�N�^�[��Ԃ�
	for (auto actor : actors_) {
		if (actor->tag() == tag) {
			return actor;
		}
	}
	//��v���Ȃ������ꍇnullptr��Ԃ�
	return nullptr;
}

void ActorManager::clear()
{
	//�S�A�N�^�[���폜
	for (auto actor : actors_) {
		delete actor;
	}
	actors_.clear();
}
