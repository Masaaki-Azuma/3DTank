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
	//�S�A�N�^�[�̍X�V
	actor_manager_.update(delta_time);
	//���S���Ă���A�N�^�[�̍폜
	actor_manager_.remove();
}

void PlayScene::draw() const
{
	//�J�����̕`��
	camera_->draw();
	//�S�A�N�^�[�̕`��
	actor_manager_.draw();
}

void PlayScene::end()
{
	//�J�����̍폜
	delete camera_;
	camera_ = nullptr;

	//���\�[�X�̉��
	gsDeleteMesh(0);
	gsDeleteMesh(1);
}
