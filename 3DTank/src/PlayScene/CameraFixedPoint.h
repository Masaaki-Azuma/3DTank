#ifndef CAMERA_FIXED_POINT_H_
#define CAMERA_FIXED_POINT_H_

#include <gslib.h>

class CameraFixedPoint
{
public:
    CameraFixedPoint(const GSvector3& eye, const GSvector3& at);
    void draw() const;

private:
    //カメラ位置
    GSvector3 eye_;
    //注視点
    GSvector3 at_;
};
#endif//!CAMERA_FIXED_POINT_H_

