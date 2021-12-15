#include "PlayScene.h"
#include <gslib.h>
#include "CameraFixedPoint.h"
#include "Stage.h"
#include "Assets.h"

void PlayScene::start()
{
	////���\�[�X�̓ǂݍ���(�X�e�[�W�Ԃŋ��ʂ��Ďg�����̂�)
	gsLoadMesh(Mesh_Player, "Assets/blue_tank.mshb");
	gsLoadMesh(Mesh_Enemy, "Assets/red_tank.mshb");
	gsLoadMesh(Mesh_CannonBall, "Assets/cannon_ball.mshb");

	gsLoadTexture(Texture_Stage, "Assets/stage.png");
	gsLoadTexture(Texture_Clear, "Assets/clear.png");

	//�J�����̍쐬
	world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 50.0f, 50.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 0.0f, 15.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//�X�e�[�W�̒ǉ�
	world_.add_stage(new Stage{ Octree_Mesh, Octree_Collide });

	//�ŏ��̃X�e�[�W��ǂݍ��݁A�ȍ~���[���h���ŃX�e�[�W�̐؂�ւ����s��
	world_.load_stage(0);
}

void PlayScene::update(float delta_time)
{
	//�V�[�����I�u�W�F�N�g�̍X�V
	world_.update(delta_time);
}

void PlayScene::draw() const
{
	//�V�[�����I�u�W�F�N�g�̕`��
	world_.draw();
}

void PlayScene::end()
{
	//���[���h�̊Ǘ���������
	world_.clear();
	//���\�[�X�̉��
	gsDeleteMesh(Mesh_Player);
	gsDeleteMesh(Mesh_Enemy);
	gsDeleteMesh(Mesh_CannonBall);
	gsDeleteTexture(Texture_Stage);
	gsDeleteTexture(Texture_Clear);
}

bool PlayScene::is_end() const
{
	//�v���C���[�����݂��Ă��Ȃ����(nullptr)�A�܂��̓X�e�[�W���I��������V�[���I��
	return !world_.find_actor("Player");
}

const std::string PlayScene::next() const
{
	return "TitleScene";
}

