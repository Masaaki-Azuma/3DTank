#ifndef RAY_H_
#define RAY_H_

#include <gslib.h>

//•ûŒü‚ğ‚ÂŒõüƒNƒ‰ƒX
class Ray
{
public:
	Ray(const GSvector3& position, const GSvector3& direction);
private:
	GSvector3 position_;
	GSvector3 direction_;
};
#endif//!RAY_H_

