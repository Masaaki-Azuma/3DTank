#include "PlayScene.h"
#include <gslib.h>
#include <GSeffect.h>
#include "CameraFixedPoint.h"
#include "Stage.h"
#include "Assets.h"

const int MaxLevel{ 10 };

PlayScene::PlayScene():
	fade_{Texture_SilhouetteBackground},
	level_{0},
	is_end_{false}
{
}

void PlayScene::start()
{
	////リソースの読み込み(ステージ間で共通して使う物のみ)
	gsLoadMesh(Mesh_Player, "Assets/Mesh/Tank/blue_tank.mshb");

	gsLoadMesh(Mesh_ImmovableEnemy, "Assets/Mesh/Tank/lightGreen_tank.mshb");
	gsLoadMesh(Mesh_ReflectionEnemy, "Assets/Mesh/Tank/darkGreen_tank.mshb");
	gsLoadMesh(Mesh_MortorEnemy, "Assets/Mesh/Tank/lightOrange_tank.mshb");
	gsLoadMesh(Mesh_BlastMortorEnemy, "Assets/Mesh/Tank/darkOrange_tank.mshb");
	gsLoadMesh(Mesh_ChaseEnemy, "Assets/Mesh/Tank/pink_tank.mshb");
	gsLoadMesh(Mesh_BounceEnemy, "Assets/Mesh/Tank/yellow_tank.mshb");
	gsLoadMesh(Mesh_PredictionEnemy, "Assets/Mesh/Tank/purple_tank.mshb");

	gsLoadMesh(Mesh_CannonBall, "Assets/cannon_ball.mshb");
	gsLoadMesh(Mesh_PlayerCannonBall, "Assets/player_cannon_ball.mshb");
	gsLoadMesh(Mesh_EnemyCannonBall, "Assets/enemy_cannon_ball.mshb");
	gsLoadMesh(Mesh_TargetSign, "Assets/target_sign.mshb");

	gsLoadTexture(Texture_Background, "Assets/background.png");
	gsLoadTexture(Texture_Stage, "Assets/stage.png");
	gsLoadTexture(Texture_Clear, "Assets/clear.png");
	gsLoadTexture(Texture_Miss, "Assets/miss.png");
	gsLoadTexture(Texture_Number, "Assets/number.png");
	gsLoadTexture(Texture_SilhouetteBackground, "Assets/silhouetteBackground.png");

	gsLoadEffect(Effect_Smoke, "Assets/Effect/Smoke.efk");

	//カメラの作成
	world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 50.0f, 50.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//ステージの作成
	world_.add_stage(new Stage{ Octree_Mesh, Octree_Collide });
	//状態を初期化
	state_ = State::Introduction;
	level_ = 9;
	is_end_ = false;
	level_image_.initialize(level_);
	//最初のステージを読み込み、以降ワールド内でステージの切り替えを行う
	world_.load_stage(level_);
}

void PlayScene::update(float delta_time)
{
	//シーンの状態によって分岐
	switch (state_) {
	case State::Introduction: update_introduction(delta_time); break;
	case State::Battle:       update_battle(delta_time);       break;
	case State::LevelClear:   update_level_clear(delta_time);  break;
	case State::LevelMiss:    update_level_miss(delta_time);   break;
	}
}

void PlayScene::draw() const
{
	//シーン内オブジェクトの描画
	world_.draw();

	//バトル状態なら処理を打ち切り
	if (state_ == State::Battle) return;

	//シーンの状態に応じて、追加描画
	switch (state_) {
	case State::Introduction:
		fade_.draw();
		level_image_.draw();
		break;
	case State::LevelClear:
		clear_image_.draw();
		fade_.draw();
		break;
	case State::LevelMiss:
		miss_image_.draw();
		break;
	}
}

void PlayScene::end()
{
	//TODO:エフェクト停止関係関数が信用ならない
	//再生中のエフェクトを削除
	gsStopAllEffects();
	//ワールドの管理物を消去
	world_.clear();
	//リソースの解放
	gsDeleteMesh(Mesh_Player);
	
	gsDeleteMesh(Mesh_ImmovableEnemy);
	gsDeleteMesh(Mesh_ReflectionEnemy);
	gsDeleteMesh(Mesh_MortorEnemy);
	gsDeleteMesh(Mesh_BlastMortorEnemy);
	gsDeleteMesh(Mesh_ChaseEnemy);
	gsDeleteMesh(Mesh_BounceEnemy);
	gsDeleteMesh(Mesh_PredictionEnemy);

	gsDeleteMesh(Mesh_CannonBall);
	gsDeleteMesh(Mesh_TargetSign);

	gsDeleteTexture(Texture_Background);
	gsDeleteTexture(Texture_Stage);
	gsDeleteTexture(Texture_Clear);
	gsDeleteTexture(Texture_Miss);
	gsDeleteTexture(Texture_Number);
	gsDeleteTexture(Texture_SilhouetteBackground);

	gsDeleteEffect(Effect_Smoke);
}

bool PlayScene::is_end() const
{
	//プレイヤーが存在していなければ(nullptr)、またはステージが終了したらシーン終了
	//return !world_.find_actor("Player");
	return is_end_;
}

const std::string PlayScene::next() const
{
	return "TitleScene";
}

void PlayScene::update_introduction(float delta_time)
{
	//フェードイン中か？
	if (fade_.is_running()) {
		fade_.update(delta_time);
		//フェードインし終わったか？
		if (fade_.is_opening()) {
			state_ = State::Battle;
		}
		return;
	}
	//レベル情報画面を更新
	level_image_.update(delta_time);
	//レベル情報画面が終了したら、フェードイン
	if (level_image_.is_end()) {
		fade_.fade_in();
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
	else if (!world_.find_actor("Player")) {
		state_ = State::LevelMiss;
		miss_image_.initialize();
	}
}

void PlayScene::update_level_clear(float delta_time)
{
	//フェードアウト中か？
	if (fade_.is_running()) {
		fade_.update(delta_time);
		//フェードアウトし終わったか？
		if (fade_.is_hiding()) {
			state_ = State::Introduction;
			//再生中のエフェクトを削除
			gsStopEffect(Effect_Smoke);
			//レベルを1進める
			++level_;
			level_image_.initialize(level_);
			//次のレベルをロード
			world_.load_stage(level_);
		}
		return;
	}

	//シーン内オブジェクトは続けて更新
	world_.update(delta_time);
	//レベルクリア画面を更新
	clear_image_.update(delta_time);
	//クリア画面が終了したら、フェードアウト
	if (clear_image_.is_end()) {
		if (level_ + 1 >= MaxLevel) {
			is_end_ = true;
			return;
		}
		fade_.fade_out();
	}
}

void PlayScene::update_level_miss(float delta_time)
{
	world_.update(delta_time);
	miss_image_.update(delta_time);
	if (miss_image_.is_end()) {
		state_ = State::Introduction;
		//再生中のエフェクトを削除
		gsStopAllEffects();
		//現在レベルをリスタート
		level_image_.initialize(level_);
		//次のレベルをロード
		world_.load_stage(level_);
	}
}

