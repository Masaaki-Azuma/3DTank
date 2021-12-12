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
	//�J�����̒ǉ�
	void add_camera(CameraFixedPoint* camera);
	//�t�B�[���h�̒ǉ�
	void add_field(Field* field);

	//�A�N�^�[�̒ǉ�
	virtual void add_actor(Actor* actor) override;
	//�A�N�^�[�̖��O����
	virtual Actor* find_actor(const std::string& name) const;
	//�A�N�^�[�̃^�O����
	virtual Actor* find_actor_with_tag(const std::string& tag) const;
	//�t�B�[���h�̎擾
	virtual Field& field() override;

private:
	//�A�N�^�[�Ǘ��I�u�W�F�N�g
	ActorManager actor_manager_;
	//��_�J����
	CameraFixedPoint* camera_{ nullptr };
	//�t�B�[���h
	Field* field_{ nullptr };
};
#endif//!WORLD_H_
