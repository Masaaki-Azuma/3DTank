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

private:
	//アクター管理オブジェクト
	ActorManager actor_manager_;
	//定点カメラ
	CameraFixedPoint* camera_{ nullptr };
	//ステージ
	Stage* stage_{ nullptr };
};
#endif//!WORLD_H_
