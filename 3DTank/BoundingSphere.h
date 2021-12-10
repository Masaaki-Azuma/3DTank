#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_

#include <gslib.h>

class BoundingSphere
{
public:
	BoundingSphere(float radius = 0.0f, const GSvector3& center = GSvector3{ 0.0f, 0.0f, 0.0f });
	//���s�ړ�
	BoundingSphere translate(const GSvector3& position) const;
	//�ϊ�
	BoundingSphere transform(const GSmatrix4& matrix) const;
	//���E�����m�̏Փ˔���
	bool intersects(const BoundingSphere& other) const;
	//�f�o�b�O�p���E���`��
	void draw() const;

	float radius() const;
	const GSvector3& center() const;
private:
	//���a
	float radius_;
	//���S���W(�����傩��̑��΍��W)
	GSvector3 center_;
};
#endif//!BOUNDING_SPHERE_H_

