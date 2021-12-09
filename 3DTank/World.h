#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "ActorManager.h"

class CameraFixedPoint;

class World : public IWorld
{
public:
	void update(float delta_time);
	void draw() const;
	void clear();
	//カメラの追加
	void add_camera(CameraFixedPoint* camera);

	//アクターの追加
	virtual void add_actor(Actor* actor) override;
private:
	//アクター管理オブジェクト
	ActorManager actor_manager_;
	//定点カメラ
	CameraFixedPoint* camera_{ nullptr };
};
#endif//!WORLD_H_
