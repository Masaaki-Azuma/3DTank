#include "PlayScene.h"
#include <gslib.h>
#include "Player.h"
#include "CameraFixedPoint.h"

void PlayScene::start()
{
	//リソースの読み込み
	gsLoadMesh(0, "Assets/tank.mshb");
	gsLoadMesh(1, "Assets/cannon_ball.mshb");
	
	//カメラの作成
	world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 50.0f, 50.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//アクターの追加
	world_.add_actor(new Player{ GSvector3{0.0f, 0.0f, 0.0f} });
}

void PlayScene::update(float delta_time)
{
	world_.update(delta_time);
}

void PlayScene::draw() const
{
	world_.draw();
}

void PlayScene::end()
{
	//ワールドの管理物を消去
	world_.clear();
	//リソースの解放
	gsDeleteMesh(0);
	gsDeleteMesh(1);
}
