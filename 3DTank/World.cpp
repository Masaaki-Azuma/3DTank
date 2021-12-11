#include "World.h"
#include "CameraFixedPoint.h"
#include "Player.h"

void World::update(float delta_time)
{
	//全アクターの更新
	actor_manager_.update(delta_time);
	//死亡しているアクターの削除
	actor_manager_.remove();
}

void World::draw() const
{
	//カメラの描画
	camera_->draw();
	//ステージの描画
	field_->draw();
	//全アクターの描画
	actor_manager_.draw();
}

void World::clear()
{
	//全アクターの削除
	actor_manager_.clear();
	//フィールドの削除
	delete field_;
	field_ = nullptr;
	//カメラの削除
	delete camera_;
	camera_ = nullptr;
}

void World::add_actor(Actor* actor)
{
	//アクターマネージャーへ中継
	actor_manager_.add(actor);
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

void World::add_field(Field* field)
{
	//既に作成されたフィールドがあれば削除
	if (field_) {
		delete field_;
		field_ = nullptr;
	}
	field_ = field;
}

Field& World::field()
{
	return *field_;
}
