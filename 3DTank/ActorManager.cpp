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

void ActorManager::add(Actor* actor)
{
	//�A�N�^�[�̒ǉ�
	actors_.push_back(actor);
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

void ActorManager::find(const std::string& name) const
{
}

void ActorManager::find_with_tag(const std::string& tag) const
{
}

void ActorManager::clear()
{
	//�S�A�N�^�[���폜
	for (auto actor : actors_) {
		delete actor;
	}
	actors_.clear();
}
