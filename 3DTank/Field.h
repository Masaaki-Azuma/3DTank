#ifndef FIELD_H_
#define FIELD_H_

#include <gslib.h>

class BoundingSphere;
class Line;

//�n�`�����Ǘ�����N���X
class Field
{
public:
	Field(GSuint mesh, GSuint collider);
	//�n�`��`��
	void draw() const;
	//���ƒn�`�̓����蔻��
	bool collide(const BoundingSphere& sphere, GSvector3* center = nullptr);
	//�����ƒn�`�̓����蔻��
	bool collide(const Line& line, GSvector3* intersect = nullptr);

private:
	//�n�`���b�V���I�N�c���[
	GSuint mesh_;
	//�n�`�R���C�_�[�I�N�c���[
	GSuint collider_;
};
#endif//!FIELD_H_

