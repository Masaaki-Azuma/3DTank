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

	gsLoadTexture(Texture_Stage, "Assets/stage.png");
	gsLoadTexture(Texture_Clear, "Assets/clear.png");

	//カメラの作成
	world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 50.0f, 50.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 0.0f, 15.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//ステージの追加
	world_.add_stage(new Stage{ Octree_Mesh, Octree_Collide });

	//最初のステージを読み込み、以降ワールド内でステージの切り替えを行う
	world_.load_stage(0);
}

void PlayScene::update(float delta_time)
{
	//シーン内オブジェクトの更新
	world_.update(delta_time);
}

void PlayScene::draw() const
{
	//シーン内オブジェクトの描画
	world_.draw();
}

void PlayScene::end()
{
	//ワールドの管理物を消去
	world_.clear();
	//リソースの解放
	gsDeleteMesh(Mesh_Player);
	gsDeleteMesh(Mesh_Enemy);
	gsDeleteMesh(Mesh_CannonBall);
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

