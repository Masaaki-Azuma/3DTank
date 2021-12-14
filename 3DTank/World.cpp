#include "World.h"
#include "CameraFixedPoint.h"
#include "Player.h"
#include "Stage.h"

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
}

void World::clear()
{
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
	stage_->load(stage);
}

Stage& World::stage()
{
	return *stage_;
}
