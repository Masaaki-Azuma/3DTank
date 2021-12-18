#include "ActorGenerator.h"
#include "IWorld.h"
#include "Player.h"
#include "Enemy.h"
#include "LevelImage.h"

ActorGenerator::ActorGenerator(IWorld* world):
	world_{world}
{
}

//ステージに応じた生成表をもとにアクターを生成
void ActorGenerator::generate(unsigned int stage)
{
	//全アクターを削除する
	world_->clear_actor();

	//ファイル名を作成
	std::string file_name = "Assets/Actor_tables/actor_generate_table" + std::to_string(stage) + ".csv";
	//ファイルを読み込み
	actor_generate_table_.load(file_name);
	//ステージに応じた自機、敵等の配置を行う
	for (int i = 0; i < actor_generate_table_.rows(); ++i) {
		//生成クラス名取得
		std::string name = actor_generate_table_.get(i, 0);
		//生成位置取得
		GSvector3 position{ actor_generate_table_.getf(i, 1), actor_generate_table_.getf(i, 2), actor_generate_table_.getf(i, 3) };
		//生成アクター
		Actor* actor{ nullptr };
		if (name == "Player") actor = new Player{ world_, position };
		else if (name == "Enemy")  actor = new Enemy{ world_, position };
		//アクターを生成
		if (actor)world_->add_actor(actor);
	}

	//ステージ情報演出を追加
	world_->add_actor(new LevelImage{ world_ });

}
