#include "BoundingSphere.h"

BoundingSphere::BoundingSphere(float radius, const GSvector3& center):
    radius_{radius}, center_{center}
{
}

BoundingSphere BoundingSphere::translate(const GSvector3& position) const
{
    return BoundingSphere{radius_, center_ + position};
}

bool BoundingSphere::intersects(const BoundingSphere& other)
{
    return gsCollisionSphereAndSphere(
        &center_, radius_, &other.center_, other.radius_) == GS_TRUE;
}

void BoundingSphere::draw() const
{
    glPushMatrix();
    glTranslatef(center_.x, center_.y, center_.z);
    glutWireSphere(radius_, 16, 16);
    glPopMatrix();
}
