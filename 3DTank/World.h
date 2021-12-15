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
	//�J�����̒ǉ�
	void add_camera(CameraFixedPoint* camera);
	//�X�e�[�W�C���X�^���X�̒ǉ�
	void add_stage(Stage* stage);
	//�S�A�N�^�[������
	void clear_actor();
	//�X�e�[�W��ǂݍ���
	void load_stage(int stage);

	//�A�N�^�[�̒ǉ�
	virtual void add_actor(Actor* actor) override;
	//�A�N�^�[�̖��O����
	virtual Actor* find_actor(const std::string& name) const;
	//�A�N�^�[�̃^�O����
	virtual Actor* find_actor_with_tag(const std::string& tag) const;
	//�X�e�[�W�̎擾
	virtual Stage& stage() override;
	//���x���̊J�n
	virtual void change_to_battle() override;
	//���x���̏I��
	virtual void change_to_level_end() override;

private:
	//�X�e�[�W�J�n��ԍX�V����
	void introduction(float delta_time);
	//�X�e�[�W�퓬��ԍX�V
	void battle(float delta_time);
	//�X�e�[�W�N���A��ԍX�V
	void level_clear(float delta_time);

	void level_end(float delta_time);

private:
	//�A�N�^�[�Ǘ��I�u�W�F�N�g
	ActorManager actor_manager_;
	//��_�J����
	CameraFixedPoint* camera_{ nullptr };
	//�X�e�[�W
	Stage* stage_{ nullptr };

	//ForDebug

	int state_;
	int level_;
};
#endif//!WORLD_H_
