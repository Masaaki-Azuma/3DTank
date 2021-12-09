#include "PlayScene.h"
#include <gslib.h>
#include "Player.h"
#include "CameraFixedPoint.h"
#include "Assets.h"

void PlayScene::start()
{
	//���\�[�X�̓ǂݍ���
	gsLoadMesh(Mesh_Player, "Assets/tank.mshb");
	gsLoadMesh(Mesh_CannonBall, "Assets/cannon_ball.mshb");
	
	//�J�����̍쐬
	world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 50.0f, 50.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//�A�N�^�[�̒ǉ�
	world_.add_actor(new Player{&world_, GSvector3{0.0f, 0.0f, 0.0f} });
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
	//���[���h�̊Ǘ���������
	world_.clear();
	//���\�[�X�̉��
	gsDeleteMesh(0);
	gsDeleteMesh(1);
}
