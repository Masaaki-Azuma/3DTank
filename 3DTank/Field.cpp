#include "Field.h"
#include "BoundingSphere.h"
#include "Assets.h"

Field::Field(GSuint mesh, GSuint collider):
	mesh_{mesh}, collider_{collider}
{
}

void Field::draw() const
{
	//�n�`�̕`��
	gsDrawOctree(Octree_Mesh);
}

bool Field::collide(const BoundingSphere& sphere, GSvector3* center)
{
	return gsOctreeCollisionSphere(
		gsGetOctree(collider_),
		&sphere.center(), sphere.radius(), center) == GS_TRUE;
}
