#ifndef STAGE_H_
#define STAGE_H_

#include <gslib.h>

class BoundingSphere;
class Line;

//�X�e�[�W�̊Ǘ��N���X
//�X�e�[�W�f�[�^�̓ǂݍ��݁A����A����ђn�`�Ƃ̏Փ˔�����s��
class Stage
{
public:
	//�R���X�g���N�^
	Stage(GSuint mesh, GSuint collider);
	~Stage();

	//TODO:load��draw���A�N�^�[�ɂ��g����̂͂ǂ��Ȃ́H

	//�X�e�[�W�̓ǂݍ���
	void load(int stage);
	//�X�e�[�W�̉��
	void clear();
	//�X�e�[�W�̍X�V
	//void update(float delta_time);
	//�X�e�[�W�̕`��
	void draw() const;

	//���ƒn�`�̓����蔻��
	bool collide(const BoundingSphere& sphere, GSvector3* center = nullptr);
	//�����ƒn�`�̓����蔻��
	bool collide(const Line& line, GSvector3* intersect = nullptr);

private:
	//�n�`���b�V��
	GSuint mesh_;
	//�n�`�R���C�_�[
	GSuint collider_;
};
#endif//!STAGE_H_

