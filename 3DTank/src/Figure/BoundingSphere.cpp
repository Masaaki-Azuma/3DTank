#include "BoundingSphere.h"

BoundingSphere::BoundingSphere(float radius, const GSvector3& center):
	radius_{radius}, center_{center}
{
}

BoundingSphere BoundingSphere::translate(const GSvector3& position) const
{
	return BoundingSphere{ radius_, center_ + position };
}

BoundingSphere BoundingSphere::transform(const GSmatrix4& matrix) const
{
	return BoundingSphere{radius_ * matrix.getScale().x, matrix.transform(center_)};
}

bool BoundingSphere::intersects(const BoundingSphere& other) const
{
	return gsCollisionSphereAndSphere(&center_, radius_, &other.center_, other.radius_);
}

void BoundingSphere::draw() const
{
	glPushMatrix();
	glTranslatef(center_.x, center_.y, center_.z);
	glutWireSphere(radius_, 16, 16);
	glPopMatrix();
}

float BoundingSphere::radius() const
{
	return radius_;
}

const GSvector3& BoundingSphere::center() const
{
	return center_;
}
