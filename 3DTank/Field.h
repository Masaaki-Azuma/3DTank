#ifndef FIELD_H_
#define FIELD_H_

#include <gslib.h>

class BoundingSphere;

//�n�`�����Ǘ�����N���X
class Field
{
public:
	Field(GSuint mesh, GSuint collider);

	bool collide(const BoundingSphere& sphere, GSvector3* center = nullptr);
private:
	//�n�`���b�V���I�N�c���[
	GSuint mesh_;
	//�n�`�R���C�_�[�I�N�c���[
	GSuint collider_;
};
#endif//!FIELD_H_

