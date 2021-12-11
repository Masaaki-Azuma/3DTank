#include "PlayScene.h"
#include <gslib.h>
#include "Player.h"
#include "Enemy.h"
#include "CameraFixedPoint.h"
#include "Field.h"
#include "Assets.h"

void PlayScene::start()
{
	//リソースの読み込み
	gsLoadOctree(Octree_Mesh, "Assets/stage_mesh.oct");
	gsLoadOctree(Octree_Collide, "Assets/stage_collide.oct");

	gsLoadMesh(Mesh_Player, "Assets/blue_tank.mshb");
	gsLoadMesh(Mesh_Enemy, "Assets/red_tank.mshb");
	gsLoadMesh(Mesh_CannonBall, "Assets/cannon_ball.mshb");

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
	world_.update(delta_time);
}

void PlayScene::draw() const
{
	//ステージの描画
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
	gsDeleteOctree(Octree_Mesh);
	gsDeleteOctree(Octree_Collide);
}
