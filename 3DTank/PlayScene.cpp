#include "PlayScene.h"
#include <gslib.h>
#include "CameraFixedPoint.h"
#include "Stage.h"
#include "Assets.h"

void PlayScene::start()
{
	////リソースの読み込み(ステージ間で共通して使う物のみ)
	gsLoadMesh(Mesh_Player, "Assets/blue_tank.mshb");
	gsLoadMesh(Mesh_Enemy, "Assets/red_tank.mshb");
	gsLoadMesh(Mesh_CannonBall, "Assets/cannon_ball.mshb");
	gsLoadMesh(Mesh_TargetSign, "Assets/target_sign.mshb");

	gsLoadTexture(Texture_Stage, "Assets/stage.png");
	gsLoadTexture(Texture_Clear, "Assets/clear.png");

	//カメラの作成
	world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 50.0f, 50.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 0.0f, 15.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//ステージの作成
	world_.add_stage(new Stage{ Octree_Mesh, Octree_Collide });

	state_ = State::Introduction;
	level_image_.initialize();
	clear_image_.initialize();
	//最初のステージを読み込み、以降ワールド内でステージの切り替えを行う
	level_ = 0;
	world_.load_stage(level_);
}

void PlayScene::update(float delta_time)
{
	switch (state_) {
	case State::Introduction: update_introduction(delta_time); break;
	case State::Battle: update_battle(delta_time); break;
	case State::LevelClear: update_level_clear(delta_time); break;
	}
	
}

void PlayScene::draw() const
{
	//シーン内オブジェクトの描画
	world_.draw();
	if (state_ == State::Introduction) {
		level_image_.draw();
	}
	else if (state_ == State::LevelClear) {
		clear_image_.draw();
	}
}

void PlayScene::end()
{
	//ワールドの管理物を消去
	world_.clear();
	//リソースの解放
	gsDeleteMesh(Mesh_Player);
	gsDeleteMesh(Mesh_Enemy);
	gsDeleteMesh(Mesh_CannonBall);
	gsDeleteMesh(Mesh_TargetSign);
	gsDeleteTexture(Texture_Stage);
	gsDeleteTexture(Texture_Clear);
}

bool PlayScene::is_end() const
{
	//プレイヤーが存在していなければ(nullptr)、またはステージが終了したらシーン終了
	return !world_.find_actor("Player");
}

const std::string PlayScene::next() const
{
	return "TitleScene";
}

void PlayScene::update_introduction(float delta_time)
{
	//レベル情報画面を更新
	level_image_.update(delta_time);
	//レベル情報画面が終了したら、戦闘画面へ遷移
	if (level_image_.is_end()) {
		state_ = State::Battle;
	}
}

void PlayScene::update_battle(float delta_time)
{
	//シーン内オブジェクトの更新
	world_.update(delta_time);
	//戦闘画面が終了したら、遷移
	if (world_.is_level_clear()) {
		state_ = State::LevelClear;
		clear_image_.initialize();
	}
}

void PlayScene::update_level_clear(float delta_time)
{
	//シーン内オブジェクトは続けて更新
	world_.update(delta_time);
	//レベルクリア画面を更新
	clear_image_.update(delta_time);
	//クリア画面が終了したら、遷移
	if (clear_image_.is_end()) {
		state_ = State::Introduction;
		level_image_.initialize();
		world_.load_stage(++level_);
	}
}

