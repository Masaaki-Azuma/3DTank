#ifndef CAMERA_FIXED_POINT_H_
#define CAMERA_FIXED_POINT_H_

#include <gslib.h>

class CameraFixedPoint
{
public:
    CameraFixedPoint(const GSvector3& eye, const GSvector3& at);
    void draw() const;

private:
    //�J�����ʒu
    GSvector3 eye_;
    //�����_
    GSvector3 at_;
};
#endif//!CAMERA_FIXED_POINT_H_

