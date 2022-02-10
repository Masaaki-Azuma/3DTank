#ifndef TANK_NUMBER_H_
#define TANK_NUMBER_H_

#include "Util/NumberTexture.h"

//残り敵数を表示する
class TankNumber
{
public:
	TankNumber();
	void draw(int level_num) const;
private:
	NumberTexture number_;
};
#endif//!TANK_NUMBER_H_
