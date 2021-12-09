#ifndef WORLD_H_
#define WORLD_H_

#include "ActorManager.h"

class CameraFixedPoint;

class World
{
public:
	World();
	~World();
	void update(float delta_time);
	void draw() const;
	void clear();
	void add_actor(Actor* actor);
	void add_camera(CameraFixedPoint* camera);
private:
	ActorManager actor_manager_;
	CameraFixedPoint* camera_{ nullptr };
};
#endif//!WORLD_H_
