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
	//現在のシーンを更新
	currentScene_->update(delta_time);
	//シーンが終了していたら、シーン遷移
	if (currentScene_->is_end()) {
		change(currentScene_->next());
	}
}

void SceneManager::draw() const
{
	//現在のシーンを描画
	currentScene_->draw();
}

void SceneManager::add(std::string name, IScene* scene)
{
	scenes_[name] = scene;
}

void SceneManager::change(std::string name)
{
	//現在のシーンを終了
	end();
	//現在のシーンを設定
	currentScene_ = scenes_[name];
	//現在のシーンの開始処理
	currentScene_->start();
}

void SceneManager::clear()
{
	//現在のシーンを終了
	end();
	//シーンを解放
	for (auto& pair : scenes_) {
		delete pair.second;
	}
	//シーンを削除
	scenes_.clear();
}

void SceneManager::end()
{
	//現在のシーンの終了処理
	currentScene_->end();
	//現在のシーンをヌルシーンに設定
	currentScene_ = &null_scene;
}
