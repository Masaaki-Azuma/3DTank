#include "CameraFixedPoint.h"

CameraFixedPoint::CameraFixedPoint(const GSvector3& eye, const GSvector3& at)
{
	eye_ = eye;
	at_ = at;
}

void CameraFixedPoint::draw() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		eye_.x, eye_.y, eye_.z,
		 at_.x,  at_.y,  at_.z,
		  0.0f,   1.0f,   0.0f
	);
}
