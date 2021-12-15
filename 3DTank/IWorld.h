#ifndef IWORLD_H_
#define IWORLD_H_

#include <string>

class Actor;
class Stage;

//ワールド抽象インターフェース
class IWorld
{
public:
	//アクターの追加
	virtual void add_actor(Actor* actor) = 0;
	//アクターの名前検索
	virtual Actor* find_actor(const std::string& name) const = 0;
	//アクターのタグ検索
	virtual Actor* find_actor_with_tag(const std::string& name) const = 0;

	//ステージの取得
	virtual Stage& stage() = 0;
	//レベルの開始
	virtual void change_to_battle() = 0;
	//レベルの終了
	virtual void change_to_level_end() = 0;
};

#endif//!IWORLD_H_
