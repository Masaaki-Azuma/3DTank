#include "World.h"
#include "CameraFixedPoint.h"
#include "Player.h"

World::World()
{
	
}

World::~World()
{
}

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
	//全アクターの描画
	actor_manager_.draw();
}

void World::clear()
{
	//全アクターの削除
	actor_manager_.clear();
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
