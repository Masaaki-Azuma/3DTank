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
	//�S�A�N�^�[�̍X�V
	actor_manager_.update(delta_time);
}

void PlayScene::draw() const
{
	//�S�A�N�^�[�̕`��
	actor_manager_.draw();
}

void PlayScene::end()
{
	//���\�[�X�̉��
	gsDeleteMesh(0);
	gsDeleteMesh(1);
}
