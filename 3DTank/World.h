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
	//�J�����̒ǉ�
	void add_camera(CameraFixedPoint* camera);

	//�A�N�^�[�̒ǉ�
	virtual void add_actor(Actor* actor) override;
private:
	//�A�N�^�[�Ǘ��I�u�W�F�N�g
	ActorManager actor_manager_;
	//��_�J����
	CameraFixedPoint* camera_{ nullptr };
};
#endif//!WORLD_H_
