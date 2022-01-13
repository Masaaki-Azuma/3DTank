#ifndef TARGET_SIGN_H_
#define TARGET_SIGN_H_

#include "Actor.h"

//砲丸の着弾位置を示す照準クラス
class TargetSign : public Actor
{
public:
	TargetSign(IWorld* world, const GSvector3& position, const Actor& owner);
	void update(float delta_time) override;
	void draw() const override;
private:
	//移動
	void move(float delta_time);
	//位置を壁の中内側に制限
	void collide_wall(const GSvector3& position);
private:
	GSvector3 offset_;  //照準の持ち主からの相対位置
	const Actor& owner_;
};
#endif//!TARGET_SIGN_H_

