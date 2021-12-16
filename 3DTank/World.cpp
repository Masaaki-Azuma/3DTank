#include "World.h"
#include "CameraFixedPoint.h"
#include "Player.h"
#include "LevelImage.h"
#include "ClearImage.h"
#include "Stage.h"
#include "ActorGenerator.h"

enum //�v���C�V�[���̏��
{
	Introduction,
	Battle,
	LevelClear,
	LevelEnd,
};

void World::update(float delta_time)
{
	//��Ԃɉ����ĕ���
	switch (state_) {
	case Introduction:
		introduction(delta_time); break;
	case Battle:
		battle(delta_time); break;
	case LevelClear:
		level_clear(delta_time); break;
	case LevelEnd:
		level_end(delta_time); break;
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
	//�SGUI�̕`��
	actor_manager_.draw_gui();
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
	//TODO:����������������̖��ʂ���Ȃ��H�|�C���^�^�̃����o�ɂ���
	//�X�e�[�W�ɉ����������\�����ƂɃA�N�^�[��z�u����
	ActorGenerator actor_generator{ this };
	actor_generator.generate(stage);

	//�X�e�[�W��񉉏o��ǉ�
	actor_manager_.add(new LevelImage{ this });
}

Stage& World::stage()
{
	return *stage_;
}

void World::change_to_battle()
{
	//���x���퓬��ԂɑJ��
	state_ = Battle;
}

void World::change_to_level_end()
{
	//���x���I����ԂɑJ��
	state_ = LevelEnd;
}

//�X�e�[�W�J�n��ԍX�V����
void World::introduction(float delta_time)
{
	//HACK:���ʃN���X�̎����Ɉˑ����Ă���
	//���x����񉉏o�̂ݍX�V
	Actor* level_image = find_actor("LevelImage");
	if (level_image) level_image->update(delta_time);
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
		state_ = LevelClear;
		actor_manager_.add(new ClearImage{ this });
	}
}

void World::level_clear(float delta_time)
{
	//HACK:battle()�ƃR�[�h�̏d��
	//�S�A�N�^�[�̍X�V
	actor_manager_.update(delta_time);
	//�S�A�N�^�[�̏Փ˔���
	actor_manager_.collide();
	//���S���Ă���A�N�^�[�̍폜
	actor_manager_.remove();
}

void World::level_end(float delta_time)
{
	//���̃X�e�[�W�ɐi��
	load_stage(++level_);
}
