#include "SceneManager.h"
#include "NullScene.h"

static NullScene null_scene;

SceneManager::SceneManager():
	currentScene_{&null_scene}
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::update(float delta_time)
{
	/*�V�[���J�ډ��o����*/
	//�V�[���B�����J���Ă��邩�H
	if (cover_.is_running()) { 
		//�V�[���B�����X�V
		cover_.update(delta_time);
		//�V�[�����B���I��������H
		if (cover_.is_closed()) {
			change(currentScene_->next());
		}
		return; //�V�[���J�ڒ��̓V�[�����X�V�����I��
	}
	
	/*�V�[���{�̏���*/
	//���݂̃V�[�����X�V
	currentScene_->update(delta_time);
	//�V�[�����I�����Ă�����A�V�[���J��
	if (currentScene_->is_end()) {
		//�V�[�����B��
		cover_.close();
	}
}

void SceneManager::draw() const
{
	//���݂̃V�[����`��
	currentScene_->draw();
	//�V�[���B����`��
	cover_.draw();
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
	//�V�[�������J���n�߂�
	cover_.open();
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