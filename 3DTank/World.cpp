#include "World.h"
#include "CameraFixedPoint.h"
#include "Player.h"
#include "Stage.h"
#include "ActorGenerator.h"

//ForDebug
#include "Assets.h"

enum //プレイシーンの状態
{
	Introduction,
	Battle,
	StageClear,
};
//TODO:update()移植中、移植前
//void World::update(float delta_time)
//{
//	//全アクターの更新
//	actor_manager_.update(delta_time);
//	//全アクターの衝突判定
//	actor_manager_.collide();
//	//死亡しているアクターの削除
//	actor_manager_.remove();
//}

//TODO:update()移植中、移植後
void World::update(float delta_time)
{
	//状態に応じて分岐
	switch (state_) {
	case Introduction:
		introduction(delta_time); break;
	case Battle:
		battle(delta_time); break;
	case StageClear:
		stage_clear(delta_time); break;
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

	//TODO:アクター化、実作業をさせない
	if (state_ == Introduction) {
		GSvector2 position_stage{ 0, 100 };
		gsDrawSprite2D(Texture_Stage, &position_stage, NULL, NULL, NULL, NULL, NULL);
	}
	else if (state_ == StageClear) {
		GSvector2 position_stage{ 0, 100 };
		gsDrawSprite2D(Texture_Clear, &position_stage, NULL, NULL, NULL, NULL, NULL);
	}
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
	//ステージに応じた生成表をもとにアクターを配置する
	ActorGenerator actor_generator{ this };
	actor_generator.generate(stage);
}

Stage& World::stage()
{
	return *stage_;
}

//ステージ開始状態更新処理
void World::introduction(float delta_time)
{
	//開始シーンの管理タイマー
	static float timer_{ 0.0f };
	//タイマーを更新
	timer_ += delta_time;
	//1秒語にバトルシーンに遷移
	if (timer_ >= 60.0f) {
		state_ = Battle;
		//タイマーの初期化
		timer_ = 0.0f;
	}
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
		state_ = StageClear;
	}
}

void World::stage_clear(float delta_time)
{
	static float timer_{ 0.0f };
	//シーン内オブジェクトの更新
	battle(delta_time);

	//タイマーを更新
	timer_ += delta_time;
	//1秒語にバトルシーンに遷移
	if (timer_ >= 60.0f) {
		//state_ = StageEnd;
		//タイマーの初期化
		timer_ = 0.0f;
		//次のステージに進む
		load_stage(++level_);
	}
}
