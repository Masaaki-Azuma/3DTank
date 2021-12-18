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
	gsLoadMesh(Mesh_TargetSign, "Assets/target_sign.mshb");

	gsLoadTexture(Texture_Stage, "Assets/stage.png");
	gsLoadTexture(Texture_Clear, "Assets/clear.png");

	//�J�����̍쐬
	world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 50.0f, 50.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 0.0f, 15.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//�X�e�[�W�̍쐬
	world_.add_stage(new Stage{ Octree_Mesh, Octree_Collide });

	state_ = State::Introduction;
	level_image_.initialize();
	clear_image_.initialize();
	//�ŏ��̃X�e�[�W��ǂݍ��݁A�ȍ~���[���h���ŃX�e�[�W�̐؂�ւ����s��
	level_ = 0;
	world_.load_stage(level_);
}

void PlayScene::update(float delta_time)
{
	switch (state_) {
	case State::Introduction: update_introduction(delta_time); break;
	case State::Battle: update_battle(delta_time); break;
	case State::LevelClear: update_level_clear(delta_time); break;
	}
	
}

void PlayScene::draw() const
{
	//�V�[�����I�u�W�F�N�g�̕`��
	world_.draw();
	if (state_ == State::Introduction) {
		level_image_.draw();
	}
	else if (state_ == State::LevelClear) {
		clear_image_.draw();
	}
}

void PlayScene::end()
{
	//���[���h�̊Ǘ���������
	world_.clear();
	//���\�[�X�̉��
	gsDeleteMesh(Mesh_Player);
	gsDeleteMesh(Mesh_Enemy);
	gsDeleteMesh(Mesh_CannonBall);
	gsDeleteMesh(Mesh_TargetSign);
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

void PlayScene::update_introduction(float delta_time)
{
	//���x������ʂ��X�V
	level_image_.update(delta_time);
	//���x������ʂ��I��������A�퓬��ʂ֑J��
	if (level_image_.is_end()) {
		state_ = State::Battle;
	}
}

void PlayScene::update_battle(float delta_time)
{
	//�V�[�����I�u�W�F�N�g�̍X�V
	world_.update(delta_time);
	//�퓬��ʂ��I��������A�J��
	if (world_.is_level_clear()) {
		state_ = State::LevelClear;
		clear_image_.initialize();
	}
}

void PlayScene::update_level_clear(float delta_time)
{
	//�V�[�����I�u�W�F�N�g�͑����čX�V
	world_.update(delta_time);
	//���x���N���A��ʂ��X�V
	clear_image_.update(delta_time);
	//�N���A��ʂ��I��������A�J��
	if (clear_image_.is_end()) {
		state_ = State::Introduction;
		level_image_.initialize();
		world_.load_stage(++level_);
	}
}

