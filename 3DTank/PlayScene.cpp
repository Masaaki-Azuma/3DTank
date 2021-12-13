#include "PlayScene.h"
#include <gslib.h>
#include "Player.h"
#include "Enemy.h"
#include "CameraFixedPoint.h"
#include "Field.h"
#include "Assets.h"

enum //�v���C�V�[���̏��
{
	Introduction,
	Battle,
	StageClear,
	StageEnd,
};

void PlayScene::start()
{
	////���\�[�X�̓ǂݍ���
	gsLoadMesh(Mesh_Player, "Assets/blue_tank.mshb");
	gsLoadMesh(Mesh_Enemy, "Assets/red_tank.mshb");
	gsLoadMesh(Mesh_CannonBall, "Assets/cannon_ball.mshb");

	gsLoadTexture(Texture_Stage, "Assets/stage.png");
	gsLoadTexture(Texture_Clear, "Assets/clear.png");

	//�J�����̍쐬
	world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 50.0f, 50.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//world_.add_camera(new CameraFixedPoint{ GSvector3{0.0f, 0.0f, 15.0f}, GSvector3{0.0f, 0.0f, 0.0f} });
	//�t�B�[���h�̒ǉ�
	world_.add_field(new Field{ Octree_Mesh, Octree_Collide });
	//�ŏ��̃X�e�[�W��ǂݍ���
	stage_ = 0;
	load_stage(stage_);
}

void PlayScene::update(float delta_time)
{
	//�V�[���̏�Ԃɂ��J��
	switch (state_) {
	case Introduction: update_introduction(delta_time); break;
	case Battle:       update_battle(delta_time); break;
	case StageClear:   update_stage_clear(delta_time); break;
	}
	
}

void PlayScene::draw() const
{
	//�V�[�����I�u�W�F�N�g�̕`��
	world_.draw();

	if (state_ == Introduction) {
		GSvector2 position_stage{ 0, 100 };
		gsDrawSprite2D(Texture_Stage, &position_stage, NULL, NULL, NULL, NULL, NULL);
	}
	else if (state_ == StageClear) {
		GSvector2 position_stage{ 0, 100 };
		gsDrawSprite2D(Texture_Clear, &position_stage, NULL, NULL, NULL, NULL, NULL);
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
	gsDeleteOctree(Octree_Mesh);
	gsDeleteOctree(Octree_Collide);
}

bool PlayScene::is_end() const
{
	//�v���C���[�����݂��Ă��Ȃ����(nullptr)�A�܂��̓X�e�[�W���I��������V�[���I��
	return !world_.find_actor("Player") || state_ == StageEnd;
}

const std::string PlayScene::next() const
{
	return "TitleScene";
}

void PlayScene::update_introduction(float delta_time)
{
	//�J�n�V�[���̊Ǘ��^�C�}�[
	static float timer_{ 0.0f };
	//�^�C�}�[���X�V
	timer_ += delta_time;
	//1�b��Ƀo�g���V�[���ɑJ��
	if (timer_ >= 60.0f) {
		state_ = Battle;
		//�^�C�}�[�̏�����
		timer_ = 0.0f;
	}
}

void PlayScene::update_battle(float delta_time)
{
	//�V�[�����I�u�W�F�N�g�̍X�V
	world_.update(delta_time);

	//�G���S�ł��Ă���΃N���A�V�[���ɑJ��
	if (!world_.find_actor_with_tag("EnemyTag")) {
		state_ = StageClear;
	}
}

void PlayScene::update_stage_clear(float delta_time)
{
	static float timer_{ 0.0f };
	//�V�[�����I�u�W�F�N�g�̍X�V
	world_.update(delta_time);

	//�^�C�}�[���X�V
	timer_ += delta_time;
	//1�b��Ƀo�g���V�[���ɑJ��
	if (timer_ >= 60.0f) {
		//state_ = StageEnd;
		//�^�C�}�[�̏�����
		timer_ = 0.0f;
		//���̃X�e�[�W�ɐi��
		load_stage(++stage_);
	}
}

void PlayScene::load_stage(unsigned int stage)
{
	//�S�A�N�^�[���폜����
	world_.clear_actor();
	//�����̃X�e�[�W���폜����
	gsDeleteOctree(Octree_Mesh);
	gsDeleteOctree(Octree_Collide);

	//Introducion��Ԃɂ���
	state_ = Introduction;
	//stage�ɉ������X�e�[�W��ǂݍ���
	gsLoadOctree(Octree_Mesh, "Assets/stage_mesh.oct");
	gsLoadOctree(Octree_Collide, "Assets/stage_collide.oct");

	
	//TODO:��������B�ȉ����u�A�N�^�[�𐶐����鏈���v�Ƃ��đ��ɈϏ�����ׂ�
	//�X�e�[�W�ɉ����������\��ǂݍ���
	std::string file_name = "Assets/Actor_tables/actor_generate_table" + std::to_string(stage) + ".csv";
	actor_generate_table_.load(file_name);
	//�X�e�[�W�ɉ��������@�A�G���̔z�u���s��
	for (int i = 0; i < actor_generate_table_.rows(); ++i) {
		//�����N���X���擾
		std::string name = actor_generate_table_.get(i, 0);
		//�����ʒu�擾
		GSvector3 position{ actor_generate_table_.getf(i, 1), actor_generate_table_.getf(i, 2), actor_generate_table_.getf(i, 3) };
		//�����A�N�^�[
		Actor* actor{ nullptr };
		if      (name == "Player") actor = new Player{ &world_, position };
		else if (name == "Enemy")  actor = new Enemy{ &world_, position };
		//�A�N�^�[�𐶐�
		if (actor)world_.add_actor(actor);
	}
	//!TODO
}
