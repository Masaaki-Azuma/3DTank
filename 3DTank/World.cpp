#include "World.h"
#include "CameraFixedPoint.h"
#include "Player.h"
#include "Stage.h"

void World::update(float delta_time)
{
	//�S�A�N�^�[�̍X�V
	actor_manager_.update(delta_time);
	//�S�A�N�^�[�̏Փ˔���
	actor_manager_.collide();
	//���S���Ă���A�N�^�[�̍폜
	actor_manager_.remove();
}

void World::draw() const
{
	//�J�����̕`��
	camera_->draw();
	//�X�e�[�W�̕`��
	stage_->draw();
	//�S�A�N�^�[�̕`��
	actor_manager_.draw();
}

void World::clear()
{
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
	stage_->load(stage);
}

Stage& World::stage()
{
	return *stage_;
}
