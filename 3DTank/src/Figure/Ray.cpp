#include "Ray.h"

Ray::Ray(const GSvector3& position, const GSvector3& direction):
	position_{position}, direction_{direction}
{
}

const GSvector3& Ray::position() const
{
	return position_;
}

const GSvector3& Ray::direction() const
{
	return direction_;
}
