#include "PlayScene.h"
#include <gslib.h>
#include "Player.h"
#include "Enemy.h"
#include "CameraFixedPoint.h"
#include "Field.h"
#include "Assets.h"

enum //プレイシーンの状態
{
	Introduction,
	Battle,
	StageClear,
	StageEnd,
};

void PlayScene::start()
{
	//シーン状態の初期化
	state_ = Introduction;
	//リソースの読み込み
	gsLoadOctree(Octree_Mesh, "Assets/stage_mesh.oct");
	gsLoadOctree(Octree_Collide, "Assets/stage_collide.oct");

	gsLoadMesh(Mesh_Player, "Assets/blue_tank.mshb");
	gsLoadMesh(Mesh_Enemy, "Assets/red_tank.mshb");
	gsLoadMesh(Mesh_CannonBall, "Assets/cannon_ball.mshb");

	gsLoadTexture(Texture_Stage, "Assets/stage.png");
	gsLoadTexture(Texture_Clear, "Assets/clear.png");

	//カメラの作成
	world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 50.0f, 50.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 0.0f, 15.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//フィールドの追加
	world_.add_field(new Field{ Octree_Mesh, Octree_Collide });
	//アクターの追加
	world_.add_actor(new Player{&world_, GSvector3{0.0f, 5.8f, 0.0f} });
	world_.add_actor(new Enemy{ &world_, GSvector3{0.0f, 5.8f, -10.0f} });
}

void PlayScene::update(float delta_time)
{
	//シーンの状態により遷移
	switch (state_) {
	case Introduction: update_introduction(delta_time); break;
	case Battle:       update_battle(delta_time); break;
	case StageClear:   update_stage_clear(delta_time); break;
	}
	
}

void PlayScene::draw() const
{
	//シーン内オブジェクトの描画
	world_.draw();

	if (state_ == Introduction) {
		GSvector2 position_stage{ 0, 100 };
		gsDrawSprite2D(Texture_Stage, &position_stage, NULL, NULL, NULL, NULL, NULL);
	}
	else if (state_ == StageClear) {
		GSvector2 position_stage{ 0, 100 };
		gsDrawSprite2D(Texture_Clear, &position_stage, NULL, NULL, NULL, NULL, NULL);
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
	gsDeleteOctree(Octree_Mesh);
	gsDeleteOctree(Octree_Collide);
}

bool PlayScene::is_end() const
{
	//プレイヤーが存在していなければ(nullptr)、またはステージが終了したらシーン終了
	return !world_.find_actor("Player") || state_ == StageEnd;
}

const std::string PlayScene::next() const
{
	return "TitleScene";
}

void PlayScene::update_introduction(float delta_time)
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

void PlayScene::update_battle(float delta_time)
{
	//シーン内オブジェクトの更新
	world_.update(delta_time);

	//敵が全滅していればクリアシーンに遷移
	if (!world_.find_actor_with_tag("EnemyTag")) {
		state_ = StageClear;
	}
}

void PlayScene::update_stage_clear(float delta_time)
{
	static float timer_{ 0.0f };
	//シーン内オブジェクトの更新
	world_.update(delta_time);

	//タイマーを更新
	timer_ += delta_time;
	//1秒語にバトルシーンに遷移
	if (timer_ >= 60.0f) {
		state_ = StageEnd;
		//タイマーの初期化
		timer_ = 0.0f;
	}
}
