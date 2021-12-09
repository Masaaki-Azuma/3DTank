#ifndef IWORLD_H_
#define IWORLD_H_

class Actor;

//ワールド抽象インターフェース
class IWorld
{
public:
	//アクターの追加
	virtual void add_actor(Actor* actor) = 0;
};

#endif//!IWORLD_H_
