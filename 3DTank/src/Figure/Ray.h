#ifndef RAY_H_
#define RAY_H_

#include <gslib.h>

//方向を持つ光線クラス
class Ray
{
public:
	Ray(const GSvector3& position, const GSvector3& direction);
	const GSvector3& position() const;
	const GSvector3& direction() const;
private:
	//光線の始点
	GSvector3 position_;
	//光線の方向
	GSvector3 direction_;
};
#endif//!RAY_H_

