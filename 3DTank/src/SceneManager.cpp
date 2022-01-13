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
	/*シーン遷移演出処理*/
	//シーン隠しが開閉しているか？
	if (cover_.is_running()) { 
		//シーン隠しを更新
		cover_.update(delta_time);
		//シーンを隠し終わったか？
		if (cover_.is_closed()) {
			change(currentScene_->next());
		}
		return; //シーン遷移中はシーンを更新せず終了
	}
	
	/*シーン本体処理*/
	//現在のシーンを更新
	currentScene_->update(delta_time);
	//シーンが終了していたら、シーン遷移
	if (currentScene_->is_end()) {
		//シーンを隠す
		cover_.close();
	}
}

void SceneManager::draw() const
{
	//現在のシーンを描画
	currentScene_->draw();
	//シーン隠しを描画
	cover_.draw();
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
	//シーンを公開し始める
	cover_.open();
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
