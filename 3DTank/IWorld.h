#ifndef IWORLD_H_
#define IWORLD_H_

class Actor;
class Field;

//ワールド抽象インターフェース
class IWorld
{
public:
	//アクターの追加
	virtual void add_actor(Actor* actor) = 0;
	//フィールドの取得
	virtual Field& field() = 0;
};

#endif//!IWORLD_H_
