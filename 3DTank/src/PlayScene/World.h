#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "ActorManager.h"

class CameraFixedPoint;
class Stage;

//ワールドクラス、仲介役クラス
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
	//ステージを読み込み
	void load_stage(int stage);

	//アクターの追加
	virtual void add_actor(Actor* actor) override;
	//アクターの名前検索
	virtual Actor* find_actor(const std::string& name) const;
	//アクターのタグ検索
	virtual Actor* find_actor_with_tag(const std::string& tag) const;
	//全アクターを消去
	virtual void clear_actor() override;

	//レベルクリア状態か？
	virtual bool is_level_clear() const override;
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
