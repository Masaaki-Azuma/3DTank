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
private:
	//�S�ẴV�[���̍폜
	void clear();
	//�V�[���̏I��
	void end();
public:
	SceneManager(const SceneManager& other) = delete;
	SceneManager& operator=(const SceneManager& other) = delete;

private:
	std::unordered_map<std::string, IScene*> scenes_;
	IScene* currentScene_;
};
#endif//!SCENE_MANAGER_H_

