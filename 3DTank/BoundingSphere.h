#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_

#include <gslib.h>

class BoundingSphere
{
public:
	BoundingSphere(float radius = 0.0f, const GSvector3& center = GSvector3{0.0f, 0.0f, 0.0f});
	BoundingSphere translate(const GSvector3& position)  const;
	bool intersects(const BoundingSphere& other);
	void draw() const;
private:
	float radius_;
	GSvector3 center_;
};
#endif//!BOUNDING_SPHERE_H_

