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
	void update(float delta_time);
	void draw() const;

	void add_scene(std::string name, IScene* scene);
	void change_scene(std::string name);

private:
	void clear();
private:
	std::unordered_map<std::string, IScene*> scenes_;
	IScene& currentScene_;
};
#endif//!SCENE_MANAGER_H_

