#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "ActorManager.h"
#include "Field.h"

class CameraFixedPoint;

class World : public IWorld
{
public:
	void update(float delta_time);
	void draw() const;
	void clear();
	//カメラの追加
	void add_camera(CameraFixedPoint* camera);
	//フィールドの追加
	void add_field(Field* field);

	//アクターの追加
	virtual void add_actor(Actor* actor) override;
	//アクターの名前検索
	virtual Actor* find_actor(const std::string& name) const;
	//アクターのタグ検索
	virtual Actor* find_actor_with_tag(const std::string& tag) const;
	//フィールドの取得
	virtual Field& field() override;

private:
	//アクター管理オブジェクト
	ActorManager actor_manager_;
	//定点カメラ
	CameraFixedPoint* camera_{ nullptr };
	//フィールド
	Field* field_{ nullptr };
};
#endif//!WORLD_H_
