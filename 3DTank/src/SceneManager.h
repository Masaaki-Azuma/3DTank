#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <string>
#include <unordered_map>
#include "SceneCover.h"

class IScene;

//シーン管理クラス
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	//現在シーンを更新
	void update(float delta_time);
	//現在シーンを描画
	void draw() const;

	//シーンの追加
	void add(std::string name, IScene* scene);
	//シーンの変更
	void change(std::string name);
	//全てのシーンの削除
	void clear();
private:
	//シーンの終了
	void end();
public:
	SceneManager(const SceneManager& other) = delete;
	SceneManager& operator=(const SceneManager& other) = delete;

private:
	std::unordered_map<std::string, IScene*> scenes_;
	IScene* currentScene_;
	SceneCover cover_;
};
#endif//!SCENE_MANAGER_H_

