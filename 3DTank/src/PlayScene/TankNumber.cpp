#include "TankNumber.h"
#include "Assets.h"

TankNumber::TankNumber():
	number_{ Texture_Number, 68, 98 }
{
}

void TankNumber::draw(int level_num) const
{
	GSvector2 position{ 700, 70 };
	gsDrawSprite2D(Texture_Play_RemainingTank, &position, NULL, NULL, NULL, NULL, NULL);
	number_.draw(GSvector2{ 1100, 60 }, std::to_string(level_num));
}
