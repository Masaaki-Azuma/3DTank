#include "Field.h"
#include "BoundingSphere.h"

Field::Field(GSuint mesh, GSuint collider):
	mesh_{mesh}, collider_{collider}
{
}

bool Field::collide(const BoundingSphere& sphere, GSvector3* center)
{
	return gsOctreeCollisionSphere(
		gsGetOctree(collider_),
		&sphere.center(), sphere.radius(), center) == GS_TRUE;
}
