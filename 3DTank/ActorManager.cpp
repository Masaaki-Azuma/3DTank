#include "ActorManager.h"
#include "Actor.h"

ActorManager::~ActorManager()
{
	clear();
}

void ActorManager::update(float delta_time)
{
	//全アクターの更新
	for (auto actor : actors_) {
		actor->update(delta_time);
	}
}

void ActorManager::draw() const
{
	//全アクターの描画
	for (auto actor : actors_) {
		actor->draw();
	}
}

void ActorManager::add(Actor* actor)
{
	//アクターの追加
	actors_.push_back(actor);
}

void ActorManager::remove()
{
	//死亡しているアクターを削除する
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
	//全アクターを削除
	for (auto actor : actors_) {
		delete actor;
	}
	actors_.clear();
}
