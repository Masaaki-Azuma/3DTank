#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "ActorManager.h"

class CameraFixedPoint;
class Stage;

class World : public IWorld
{
public:
	void update(float delta_time);
	void draw() const;
	void clear();
	//カメラの追加
	void add_camera(CameraFixedPoint* camera);
	//ステージインスタンスの追加
	void add_stage(Stage* stage);
	//全アクターを消去
	void clear_actor();
	//ステージを読み込み
	void load_stage(int stage);

	//アクターの追加
	virtual void add_actor(Actor* actor) override;
	//アクターの名前検索
	virtual Actor* find_actor(const std::string& name) const;
	//アクターのタグ検索
	virtual Actor* find_actor_with_tag(const std::string& tag) const;
	//ステージの取得
	virtual Stage& stage() override;
	//レベルの開始
	virtual void change_to_battle() override;
	//レベルの終了
	virtual void change_to_level_end() override;

private:
	//ステージ開始状態更新処理
	void introduction(float delta_time);
	//ステージ戦闘状態更新
	void battle(float delta_time);
	//ステージクリア状態更新
	void level_clear(float delta_time);

	void level_end(float delta_time);

private:
	//アクター管理オブジェクト
	ActorManager actor_manager_;
	//定点カメラ
	CameraFixedPoint* camera_{ nullptr };
	//ステージ
	Stage* stage_{ nullptr };

	//ForDebug

	int state_;
	int level_;
};
#endif//!WORLD_H_
