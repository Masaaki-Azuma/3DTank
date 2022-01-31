#ifndef WORLD_H_
#define WORLD_H_

#include "IWorld.h"
#include "ActorManager.h"

class CameraFixedPoint;
class Stage;

//���[���h�N���X�A������N���X
class World : public IWorld
{
public:
	void update(float delta_time);
	void draw() const;
	void clear();
	//�J�����̒ǉ�
	void add_camera(CameraFixedPoint* camera);
	//�X�e�[�W�C���X�^���X�̒ǉ�
	void add_stage(Stage* stage);
	//�X�e�[�W��ǂݍ���
	void load_stage(int stage);

	//�A�N�^�[�̒ǉ�
	virtual void add_actor(Actor* actor) override;
	//�A�N�^�[�̖��O����
	virtual Actor* find_actor(const std::string& name) const;
	//�A�N�^�[�̃^�O����
	virtual Actor* find_actor_with_tag(const std::string& tag) const;
	//�S�A�N�^�[������
	virtual void clear_actor() override;

	//���x���N���A��Ԃ��H
	virtual bool is_level_clear() const override;
	//�X�e�[�W�̎擾
	virtual Stage& stage() override;

private:
	//�A�N�^�[�Ǘ��I�u�W�F�N�g
	ActorManager actor_manager_;
	//��_�J����
	CameraFixedPoint* camera_{ nullptr };
	//�X�e�[�W
	Stage* stage_{ nullptr };
};
#endif//!WORLD_H_
