#ifndef IWORLD_H_
#define IWORLD_H_

#include <string>

class Actor;
class Field;

//ワールド抽象インターフェース
class IWorld
{
public:
	//アクターの追加
	virtual void add_actor(Actor* actor) = 0;
	//アクターの名前検索
	virtual void find_actor(const std::string& name) const = 0;
	//アクターのタグ検索
	virtual void find_actor_with_tag(const std::string& name) const = 0;

	//フィールドの取得
	virtual Field& field() = 0;
};

#endif//!IWORLD_H_
