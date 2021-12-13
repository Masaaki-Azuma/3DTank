#ifndef ACTOR_GANERATOR_H_
#define ACTOR_GANERATOR_H_

#include "CsvReader.h"

class IWorld;

//ステージ数をもとにアクター群を生成するクラス
class ActorGenerator
{
public:
	ActorGenerator(IWorld* world);
	//アクターを生成
	void generate(unsigned int stage);

private:
	IWorld* world_;
	CsvReader actor_generate_table_;
};
#endif//!ACTOR_GANERATOR_H_

