#ifndef TANK_NUMBER_H_
#define TANK_NUMBER_H_

#include "Util/NumberTexture.h"

//c‚è“G”‚ğ•\¦‚·‚é
class TankNumber
{
public:
	TankNumber();
	void draw(int level_num) const;
private:
	NumberTexture number_;
};
#endif//!TANK_NUMBER_H_
