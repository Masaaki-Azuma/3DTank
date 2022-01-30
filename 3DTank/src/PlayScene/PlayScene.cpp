#include "PlayScene.h"
#include <gslib.h>
#include <GSeffect.h>
#include <GSmusic.h>
#include "CameraFixedPoint.h"
#include "Stage.h"
#include "Assets.h"
#include "Sound.h"

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

	gsLoadSE(Se_StartStage, "Assets/Sound/SE/start.wav", 1, GWAVE_DEFAULT);
	//gsLoadSE(Se_ChangeStage, "Assets/Sound/SE/change_stage.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(Se_ClearStage, "Assets/Sound/SE/stage_clear.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(Se_HitEnemy, "Assets/Sound/SE/hit.wav", 2, GWAVE_DEFAULT);
	gsLoadSE(Se_PlayerMove, "Assets/Sound/SE/running_tank01.wav", 1, GWAVE_WAIT);
	gsLoadSE(Se_EnemyMove, "Assets/Sound/SE/running_tank02.wav", 1, GWAVE_WAIT);
	gsLoadSE(Se_Bomb, "Assets/Sound/SE/bomb.wav", 3, GWAVE_DEFAULT);

	gsLoadMusic(Music_Battle, "Assets/Sound/BGM/battle.mp3", GS_TRUE);

	//カメラの作成
	world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 50.0f, 50.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//ステージの作成
	world_.add_stage(new Stage{ Octree_Mesh, Octree_Collide });
	//状態を初期化
	state_ = State::Introduction;
	level_ = 0;
	is_end_ = false;
	level_image_.initialize(level_);
	//最初のステージを読み込み、以降ワールド内でステージの切り替えを行う
	world_.load_stage(level_);
	//BGMをバインド
	gsBindMusic(Music_Battle);
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

	if (!pause_.is_end()) {
		pause_.draw();
	}
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
	//再生中のエフェクトを削除
	gsStopAllEffects();
	//ポーズシーンのリソースを解放
	pause_.end();
	//ワールドの管理物を消去
	world_.clear();
	//BGMを停止
	gsStopMusic();
	//リソースの解放
	gsDeleteMesh(Mesh_Player);
	
	gsDeleteMesh(Mesh_ImmovableEnemy);
	gsDeleteMesh(Mesh_ReflectionEnemy);
	gsDeleteMesh(Mesh_MortorEnemy);
	gsDeleteMesh(Mesh_BlastMortorEnemy);
	gsDeleteMesh(Mesh_ChaseEnemy);
	gsDeleteMesh(Mesh_BounceEnemy);
	gsDeleteMesh(Mesh_PredictionEnemy);

	gsDeleteMesh(Mesh_PlayerCannonBall);
	gsDeleteMesh(Mesh_EnemyCannonBall);
	gsDeleteMesh(Mesh_TargetSign);

	gsDeleteTexture(Texture_Background);
	gsDeleteTexture(Texture_Stage);
	gsDeleteTexture(Texture_Clear);
	gsDeleteTexture(Texture_Miss);
	gsDeleteTexture(Texture_Number);
	gsDeleteTexture(Texture_SilhouetteBackground);

	gsDeleteEffect(Effect_Smoke);

	gsDeleteSE(Se_StartStage);
	gsDeleteSE(Se_ClearStage);
	//gsDeleteSE(Se_ChangeStage);
	gsDeleteSE(Se_HitEnemy);
	gsDeleteSE(Se_PlayerMove);
	gsDeleteSE(Se_EnemyMove);
	gsDeleteSE(Se_Bomb);

	gsDeleteMusic(Music_Battle);
}

bool PlayScene::is_end() const
{
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
		//BGMを再生
		gsPlayMusic();
		fade_.fade_in();
	}
}

void PlayScene::update_battle(float delta_time)
{
	/*ポーズ処理*/
	//ポーズ中はポーズ画面のみを更新
	if (!pause_.is_end()) {
		pause_.update(delta_time);
		if (pause_.is_end() && pause_.next() == "TitleScene") {
			is_end_ = true;
		}
		return;
	}
	//ポーズキーでポーズ
	if (gsGetKeyTrigger(GKEY_X) && pause_.is_end()) {
		pause_.start();
		return;
	}

	/*メインゲーム処理*/
	//シーン内オブジェクトの更新
	world_.update(delta_time);
	//戦闘画面が終了したら、遷移
	if (world_.is_level_clear()) {
		state_ = State::LevelClear;
		//一旦全音源を停止
		gsStopSound();
		gsStopMusic();
		clear_image_.initialize();
	}
	else if (!world_.find_actor("Player")) {
		state_ = State::LevelMiss;
		gsStopSound();
		miss_image_.initialize();
	}
}

void PlayScene::update_level_clear(float delta_time)
{
	/*フェード処理*/
	//フェードアウト中か？
	if (fade_.is_running()) {
		fade_.update(delta_time);
		//フェードアウトし終わったか？
		if (fade_.is_hiding()) {
			state_ = State::Introduction;
			//レベルを1進める
			++level_;
			level_image_.initialize(level_);
			//次のレベルをロード
			world_.load_stage(level_);
		}
		return;
	}

	/*クリア画面処理*/
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
		//現在レベルをリスタート
		level_image_.initialize(level_);
		//次のレベルをロード
		world_.load_stage(level_);
	}
}

