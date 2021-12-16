#include "World.h"
#include "CameraFixedPoint.h"
#include "Player.h"
#include "LevelImage.h"
#include "ClearImage.h"
#include "Stage.h"
#include "ActorGenerator.h"

enum //プレイシーンの状態
{
	Introduction,
	Battle,
	LevelClear,
	LevelEnd,
};

void World::update(float delta_time)
{
	//状態に応じて分岐
	switch (state_) {
	case Introduction:
		introduction(delta_time); break;
	case Battle:
		battle(delta_time); break;
	case LevelClear:
		level_clear(delta_time); break;
	case LevelEnd:
		level_end(delta_time); break;
	}
	
}

void World::draw() const
{
	//カメラの描画
	camera_->draw();
	//ステージの描画
	stage_->draw();
	//全アクターの描画
	actor_manager_.draw();
	//全GUIの描画
	actor_manager_.draw_gui();
}

void World::clear()
{
	//ステージ番号を0に
	level_ = 0;
	//全アクターの削除
	clear_actor();
	//ステージの削除
	delete stage_;
	stage_ = nullptr;
	//カメラの削除
	delete camera_;
	camera_ = nullptr;
}

void World::add_actor(Actor* actor)
{
	//アクターマネージャーへ中継
	actor_manager_.add(actor);
}

Actor* World::find_actor(const std::string& name) const
{
	//アクターマネージャーに中継
	return actor_manager_.find(name);
}

Actor* World::find_actor_with_tag(const std::string& tag) const
{
	//アクターマネージャーに中継
	return actor_manager_.find_with_tag(tag);
}

void World::add_camera(CameraFixedPoint* camera)
{
	//既に作成されたカメラがあったら削除
	if (camera_) {
		delete camera_;
		camera_ = nullptr;
	}
	//追加
	camera_ = camera;
}

void World::add_stage(Stage* stage)
{
	//既に作成されたステージがあれば削除
	if (stage_) {
		delete stage_;
		stage_ = nullptr;
	}
	stage_ = stage;
}

void World::clear_actor()
{
	//全アクターの削除
	actor_manager_.clear();
}

void World::load_stage(int stage)
{
	//Introducion状態にする
	state_ = Introduction;

	//ステージの読み込み（消去も行う）
	stage_->load(stage);

	//全アクターを削除する
	clear_actor();
	//TODO:いちいち生成するの無駄じゃない？ポインタ型のメンバにする
	//ステージに応じた生成表をもとにアクターを配置する
	ActorGenerator actor_generator{ this };
	actor_generator.generate(stage);

	//ステージ情報演出を追加
	actor_manager_.add(new LevelImage{ this });
}

Stage& World::stage()
{
	return *stage_;
}

void World::change_to_battle()
{
	//レベル戦闘状態に遷移
	state_ = Battle;
}

void World::change_to_level_end()
{
	//レベル終了状態に遷移
	state_ = LevelEnd;
}

//ステージ開始状態更新処理
void World::introduction(float delta_time)
{
	//HACK:下位クラスの実装に依存している
	//レベル情報演出のみ更新
	Actor* level_image = find_actor("LevelImage");
	if (level_image) level_image->update(delta_time);
}

//
void World::battle(float delta_time)
{
	//全アクターの更新
	actor_manager_.update(delta_time);
	//全アクターの衝突判定
	actor_manager_.collide();
	//死亡しているアクターの削除
	actor_manager_.remove();

	//敵が全滅していればクリアシーンに遷移
	if (!find_actor_with_tag("EnemyTag")) {
		state_ = LevelClear;
		actor_manager_.add(new ClearImage{ this });
	}
}

void World::level_clear(float delta_time)
{
	//HACK:battle()とコードの重複
	//全アクターの更新
	actor_manager_.update(delta_time);
	//全アクターの衝突判定
	actor_manager_.collide();
	//死亡しているアクターの削除
	actor_manager_.remove();
}

void World::level_end(float delta_time)
{
	//次のステージに進む
	load_stage(++level_);
}
