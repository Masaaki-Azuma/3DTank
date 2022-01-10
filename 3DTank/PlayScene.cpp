#include "PlayScene.h"
#include <gslib.h>
#include "CameraFixedPoint.h"
#include "Stage.h"
#include "Assets.h"

PlayScene::PlayScene():
	fade_{Texture_SilhouetteBackground}
{
}

void PlayScene::start()
{
	////���\�[�X�̓ǂݍ���(�X�e�[�W�Ԃŋ��ʂ��Ďg�����̂�)
	gsLoadMesh(Mesh_Player, "Assets/Mesh/Tank/blue_tank.mshb");

	//gsLoadMesh(Mesh_Enemy, "Assets/Mesh/Tank/red_tank.mshb");
	gsLoadMesh(Mesh_ImmovableEnemy, "Assets/Mesh/Tank/lightGreen_tank.mshb");
	gsLoadMesh(Mesh_ReflectionEnemy, "Assets/Mesh/Tank/darkGreen_tank.mshb");
	gsLoadMesh(Mesh_MortorEnemy, "Assets/Mesh/Tank/lightOrange_tank.mshb");
	gsLoadMesh(Mesh_BlastMortorEnemy, "Assets/Mesh/Tank/darkOrange_tank.mshb");
	gsLoadMesh(Mesh_ChaseEnemy, "Assets/Mesh/Tank/pink_tank.mshb");
	gsLoadMesh(Mesh_BounceEnemy, "Assets/Mesh/Tank/yellow_tank.mshb");
	gsLoadMesh(Mesh_PredictionEnemy, "Assets/Mesh/Tank/purple_tank.mshb");

	gsLoadMesh(Mesh_CannonBall, "Assets/cannon_ball.mshb");
	gsLoadMesh(Mesh_TargetSign, "Assets/target_sign.mshb");

	gsLoadTexture(Texture_Background, "Assets/background.png");
	gsLoadTexture(Texture_Stage, "Assets/stage.png");
	gsLoadTexture(Texture_Clear, "Assets/clear.png");
	gsLoadTexture(Texture_Miss, "Assets/miss.png");
	gsLoadTexture(Texture_Number, "Assets/number.png");
	gsLoadTexture(Texture_SilhouetteBackground, "Assets/silhouetteBackground.png");

	//�J�����̍쐬
	world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 50.0f, 50.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 0.0f, 15.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//�X�e�[�W�̍쐬
	world_.add_stage(new Stage{ Octree_Mesh, Octree_Collide });

	state_ = State::Introduction;
	level_ = 6;
	level_image_.initialize(level_);
	clear_image_.initialize();
	//�ŏ��̃X�e�[�W��ǂݍ��݁A�ȍ~���[���h���ŃX�e�[�W�̐؂�ւ����s��
	world_.load_stage(level_);
}

void PlayScene::update(float delta_time)
{
	switch (state_) {
	case State::Introduction: update_introduction(delta_time); break;
	case State::Battle: update_battle(delta_time); break;
	case State::LevelClear: update_level_clear(delta_time); break;
	case State::LevelMiss: update_level_miss(delta_time); break;
	}
}

void PlayScene::draw() const
{
	//�V�[�����I�u�W�F�N�g�̕`��
	world_.draw();

	if (state_ == State::Battle) return;

	if (state_ == State::Introduction) {
		fade_.draw();
		level_image_.draw();
	}
	else if (state_ == State::LevelClear) {
		clear_image_.draw();
		fade_.draw();
	}
	else if (state_ == State::LevelMiss) {
		miss_image_.draw();
	}
}

void PlayScene::end()
{
	//���[���h�̊Ǘ���������
	world_.clear();
	//���\�[�X�̉��
	gsDeleteMesh(Mesh_Player);
	
	gsDeleteMesh(Mesh_ImmovableEnemy);
	gsDeleteMesh(Mesh_ReflectionEnemy);
	gsDeleteMesh(Mesh_MortorEnemy);
	gsDeleteMesh(Mesh_BlastMortorEnemy);
	gsDeleteMesh(Mesh_ChaseEnemy);
	gsDeleteMesh(Mesh_BounceEnemy);
	gsDeleteMesh(Mesh_PredictionEnemy);

	gsDeleteMesh(Mesh_CannonBall);
	gsDeleteMesh(Mesh_TargetSign);

	gsDeleteTexture(Texture_Background);
	gsDeleteTexture(Texture_Stage);
	gsDeleteTexture(Texture_Clear);
	gsDeleteTexture(Texture_Miss);
	gsDeleteTexture(Texture_Number);
	gsDeleteTexture(Texture_SilhouetteBackground);
}

bool PlayScene::is_end() const
{
	//�v���C���[�����݂��Ă��Ȃ����(nullptr)�A�܂��̓X�e�[�W���I��������V�[���I��
	//return !world_.find_actor("Player");
	return false;
}

const std::string PlayScene::next() const
{
	return "TitleScene";
}

void PlayScene::update_introduction(float delta_time)
{
	//�t�F�[�h�C�������H
	if (fade_.is_running()) {
		fade_.update(delta_time);
		//�t�F�[�h�C�����I��������H
		if (fade_.is_opening()) {
			state_ = State::Battle;
		}
		return;
	}
	//���x������ʂ��X�V
	level_image_.update(delta_time);
	//���x������ʂ��I��������A�t�F�[�h�C��
	if (level_image_.is_end()) {
		fade_.fade_in();
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
	else if (!world_.find_actor("Player")) {
		state_ = State::LevelMiss;
		miss_image_.initialize();
	}
}

void PlayScene::update_level_clear(float delta_time)
{
	//�t�F�[�h�A�E�g�����H
	if (fade_.is_running()) {
		fade_.update(delta_time);
		//�t�F�[�h�A�E�g���I��������H
		if (fade_.is_hiding()) {
			state_ = State::Introduction;
			//���x����1�i�߂�
			++level_;
			level_image_.initialize(level_);
			//���̃��x�������[�h
			world_.load_stage(level_);
		}
		return;
	}

	//�V�[�����I�u�W�F�N�g�͑����čX�V
	world_.update(delta_time);
	//���x���N���A��ʂ��X�V
	clear_image_.update(delta_time);
	//�N���A��ʂ��I��������A�t�F�[�h�A�E�g
	if (clear_image_.is_end()) {
		fade_.fade_out();
	}
}

void PlayScene::update_level_miss(float delta_time)
{
	world_.update(delta_time);
	miss_image_.update(delta_time);
	if (miss_image_.is_end()) {
		state_ = State::Introduction;
		//���݃��x�������X�^�[�g
		level_image_.initialize(level_);
		//���̃��x�������[�h
		world_.load_stage(level_);
	}
}

