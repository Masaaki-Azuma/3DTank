#include "World.h"
#include "CameraFixedPoint.h"
#include "Player.h"

World::World()
{
	
}

World::~World()
{
}

void World::update(float delta_time)
{
	//�S�A�N�^�[�̍X�V
	actor_manager_.update(delta_time);
	//���S���Ă���A�N�^�[�̍폜
	actor_manager_.remove();
}

void World::draw() const
{
	//�J�����̕`��
	camera_->draw();
	//�S�A�N�^�[�̕`��
	actor_manager_.draw();
}

void World::clear()
{
	//�S�A�N�^�[�̍폜
	actor_manager_.clear();
	//�J�����̍폜
	delete camera_;
	camera_ = nullptr;
}

void World::add_actor(Actor* actor)
{
	//�A�N�^�[�}�l�[�W���[�֒��p
	actor_manager_.add(actor);
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
