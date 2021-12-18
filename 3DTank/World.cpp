#include "World.h"
#include "CameraFixedPoint.h"
#include "Player.h"
#include "LevelImage.h"
#include "ClearImage.h"
#include "Stage.h"
#include "ActorGenerator.h"

void World::update(float delta_time)
{
	//全アクターの更新
	actor_manager_.update(delta_time);
	//全アクターの衝突判定
	actor_manager_.collide();
	//死亡しているアクターの削除
	actor_manager_.remove();
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
	//全アクターの削除
	actor_manager_.clear();
	//ステージの削除
	delete stage_;
	stage_ = nullptr;
	//カメラの削除
	delete camera_;
	camera_ = nullptr;
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

void World::load_stage(int stage)
{
	//TODO:以下を別のクラスに委譲し、1メソッドでステージの切り替えがしたい
	//ステージの読み込み（消去も行う）
	stage_->load(stage);
	//アクターを配置する
	static ActorGenerator actor_generator{ this };
	actor_generator.generate(stage);
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

void World::clear_actor()
{
	//全アクターの削除
	actor_manager_.clear();
}

bool World::is_level_clear() const
{
	return !actor_manager_.find_with_tag("EnemyTag");
}

Stage& World::stage()
{
	return *stage_;
}

