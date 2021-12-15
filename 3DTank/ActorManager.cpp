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

void ActorManager::draw_gui() const
{
	//全GUIの描画
	for (auto actor : actors_) {
		actor->draw_gui();
	}
}

void ActorManager::add(Actor* actor)
{
	//アクターの追加
	actors_.push_back(actor);
}

void ActorManager::collide()
{
	//アクター同士の全組み合わせで衝突判定を行う
	for (auto i = actors_.begin(); i != actors_.end(); ++i) {
		for (auto j = std::next(i); j != actors_.end(); ++j) {
			(*i)->collide(**j);
		}
	}
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

Actor* ActorManager::find(const std::string& name) const
{
	//名前が一致したアクターを返す
	for (auto actor : actors_) {
		if (actor->name() == name) {
			return actor;
		}
	}
	//一致しなかった場合nullptrを返す
	return nullptr;
}

Actor* ActorManager::find_with_tag(const std::string& tag) const
{
	//タグが一致したアクターを返す
	for (auto actor : actors_) {
		if (actor->tag() == tag) {
			return actor;
		}
	}
	//一致しなかった場合nullptrを返す
	return nullptr;
}

void ActorManager::clear()
{
	//全アクターを削除
	for (auto actor : actors_) {
		delete actor;
	}
	actors_.clear();
}
