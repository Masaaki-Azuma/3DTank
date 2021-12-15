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
	//全アクターの更新
	void update(float delta_time);
	//全アクターの描画
	void draw() const;
	//全GUIの描画
	void draw_gui() const;

	//アクターの追加
	void add(Actor* actor);
	//全アクター同士の衝突判定
	void collide();
	//死亡アクターの削除
	void remove();
	//名前で検索
	Actor* find(const std::string& name) const;
	//タグで検索
	Actor* find_with_tag(const std::string& tag) const;
	void clear();

private:
	std::list<Actor*> actors_;
};
#endif//!ACTOR_MANGER_H_

