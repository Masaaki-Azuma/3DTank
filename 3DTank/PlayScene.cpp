#include "PlayScene.h"
#include <gslib.h>
#include "Player.h"

void PlayScene::start()
{
	gsLoadMesh(0, "Assets/tank.mshb");
	gsLoadMesh(1, "Assets/cannon_ball.mshb");
	actor_manager_.add(new Player{ GSvector3{0.0f, 0.0f, 0.0f} });
}

void PlayScene::update(float delta_time)
{
	//全アクターの更新
	actor_manager_.update(delta_time);
}

void PlayScene::draw() const
{
	//全アクターの描画
	actor_manager_.draw();
}

void PlayScene::end()
{
	//リソースの解放
	gsDeleteMesh(0);
	gsDeleteMesh(1);
}
