#include "World.h"
#include "CameraFixedPoint.h"
#include "Player.h"
#include "Stage.h"
#include "ActorGenerator.h"

//ForDebug
#include "Assets.h"

enum //�v���C�V�[���̏��
{
	Introduction,
	Battle,
	StageClear,
};
//TODO:update()�ڐA���A�ڐA�O
//void World::update(float delta_time)
//{
//	//�S�A�N�^�[�̍X�V
//	actor_manager_.update(delta_time);
//	//�S�A�N�^�[�̏Փ˔���
//	actor_manager_.collide();
//	//���S���Ă���A�N�^�[�̍폜
//	actor_manager_.remove();
//}

//TODO:update()�ڐA���A�ڐA��
void World::update(float delta_time)
{
	//��Ԃɉ����ĕ���
	switch (state_) {
	case Introduction:
		introduction(delta_time); break;
	case Battle:
		battle(delta_time); break;
	case StageClear:
		stage_clear(delta_time); break;
	}
	
}

void World::draw() const
{
	//�J�����̕`��
	camera_->draw();
	//�X�e�[�W�̕`��
	stage_->draw();
	//�S�A�N�^�[�̕`��
	actor_manager_.draw();

	//TODO:�A�N�^�[���A����Ƃ������Ȃ�
	if (state_ == Introduction) {
		GSvector2 position_stage{ 0, 100 };
		gsDrawSprite2D(Texture_Stage, &position_stage, NULL, NULL, NULL, NULL, NULL);
	}
	else if (state_ == StageClear) {
		GSvector2 position_stage{ 0, 100 };
		gsDrawSprite2D(Texture_Clear, &position_stage, NULL, NULL, NULL, NULL, NULL);
	}
}

void World::clear()
{
	//�X�e�[�W�ԍ���0��
	level_ = 0;
	//�S�A�N�^�[�̍폜
	clear_actor();
	//�X�e�[�W�̍폜
	delete stage_;
	stage_ = nullptr;
	//�J�����̍폜
	delete camera_;
	camera_ = nullptr;
}

void World::add_actor(Actor* actor)
{
	//�A�N�^�[�}�l�[�W���[�֒��p
	actor_manager_.add(actor);
}

Actor* World::find_actor(const std::string& name) const
{
	//�A�N�^�[�}�l�[�W���[�ɒ��p
	return actor_manager_.find(name);
}

Actor* World::find_actor_with_tag(const std::string& tag) const
{
	//�A�N�^�[�}�l�[�W���[�ɒ��p
	return actor_manager_.find_with_tag(tag);
}

void World::add_camera(CameraFixedPoint* camera)
{
	//���ɍ쐬���ꂽ�J��������������폜
	if (camera_) {
		delete camera_;
		camera_ = nullptr;
	}
	//�ǉ�
	camera_ = camera;
}

void World::add_stage(Stage* stage)
{
	//���ɍ쐬���ꂽ�X�e�[�W������΍폜
	if (stage_) {
		delete stage_;
		stage_ = nullptr;
	}
	stage_ = stage;
}

void World::clear_actor()
{
	//�S�A�N�^�[�̍폜
	actor_manager_.clear();
}

void World::load_stage(int stage)
{
	//Introducion��Ԃɂ���
	state_ = Introduction;

	//�X�e�[�W�̓ǂݍ��݁i�������s���j
	stage_->load(stage);

	//�S�A�N�^�[���폜����
	clear_actor();
	//�X�e�[�W�ɉ����������\�����ƂɃA�N�^�[��z�u����
	ActorGenerator actor_generator{ this };
	actor_generator.generate(stage);
}

Stage& World::stage()
{
	return *stage_;
}

//�X�e�[�W�J�n��ԍX�V����
void World::introduction(float delta_time)
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

//
void World::battle(float delta_time)
{
	//�S�A�N�^�[�̍X�V
	actor_manager_.update(delta_time);
	//�S�A�N�^�[�̏Փ˔���
	actor_manager_.collide();
	//���S���Ă���A�N�^�[�̍폜
	actor_manager_.remove();

	//�G���S�ł��Ă���΃N���A�V�[���ɑJ��
	if (!find_actor_with_tag("EnemyTag")) {
		state_ = StageClear;
	}
}

void World::stage_clear(float delta_time)
{
	static float timer_{ 0.0f };
	//�V�[�����I�u�W�F�N�g�̍X�V
	battle(delta_time);

	//�^�C�}�[���X�V
	timer_ += delta_time;
	//1�b��Ƀo�g���V�[���ɑJ��
	if (timer_ >= 60.0f) {
		//state_ = StageEnd;
		//�^�C�}�[�̏�����
		timer_ = 0.0f;
		//���̃X�e�[�W�ɐi��
		load_stage(++level_);
	}
}
