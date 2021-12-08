#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <string>
#include <unordered_map>

class IScene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	//���݃V�[�����X�V
	void update(float delta_time);
	//���݃V�[����`��
	void draw() const;

	//�V�[���̒ǉ�
	void add(std::string name, IScene* scene);
	//�V�[���̕ύX
	void change(std::string name);
	//�V�[���̏I��
	void end();

private:
	void clear();
private:
	std::unordered_map<std::string, IScene*> scenes_;
	IScene* currentScene_;
};
#endif//!SCENE_MANAGER_H_

