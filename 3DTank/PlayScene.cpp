#include "PlayScene.h"
#include <gslib.h>
#include "Player.h"
#include "CameraFixedPoint.h"

void PlayScene::start()
{
	gsLoadMesh(0, "Assets/tank.mshb");
	gsLoadMesh(1, "Assets/cannon_ball.mshb");
	
	camera_ = new CameraFixedPoint{ GSvector3{0.0f, 50.0f, 50.0f}, GSvector3{0.0f, 0.0f, 0.0f} };
	actor_manager_.add(new Player{ GSvector3{0.0f, 0.0f, 0.0f} });
}

void PlayScene::update(float delta_time)
{
	//全アクターの更新
	actor_manager_.update(delta_time);
	//死亡しているアクターの削除
	actor_manager_.remove();
}

void PlayScene::draw() const
{
	//カメラの描画
	camera_->draw();
	//全アクターの描画
	actor_manager_.draw();
}

void PlayScene::end()
{
	//カメラの削除
	delete camera_;
	camera_ = nullptr;

	//リソースの解放
	gsDeleteMesh(0);
	gsDeleteMesh(1);
}
