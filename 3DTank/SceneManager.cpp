#include "SceneManager.h"
#include "NullScene.h"

static NullScene null_scene;

SceneManager::SceneManager():
	currentScene_{&null_scene}
{
}

SceneManager::~SceneManager()
{
	clear();
}

void SceneManager::update(float delta_time)
{
	currentScene_->update(delta_time);
}

void SceneManager::draw() const
{
	currentScene_->draw();
}

void SceneManager::add(std::string name, IScene* scene)
{
	scenes_[name] = scene;
}

void SceneManager::change(std::string name)
{
	//���݂̃V�[�����I��
	end();
	//���݂̃V�[����ݒ�
	currentScene_ = scenes_[name];
	//���݂̃V�[���̊J�n����
	currentScene_->start();
}

void SceneManager::clear()
{
	//���݂̃V�[�����I��
	end();
	//�V�[�������
	for (auto& pair : scenes_) {
		delete pair.second;
	}
	//�V�[�����폜
	scenes_.clear();
}

void SceneManager::end()
{
	//���݂̃V�[���̏I������
	currentScene_->end();
	//���݂̃V�[�����k���V�[���ɐݒ�
	currentScene_ = &null_scene;
}
