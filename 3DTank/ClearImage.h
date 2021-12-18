#ifndef CLEAR_IAMGE_H_
#define CLEAR_IAMGE_H_

#include "Actor.h"

class IWorld;

//クリア演出を管理するクラス。ミニシーン
class ClearImage : public Actor
{
public:
	ClearImage();
	void initialize();
	virtual void update(float delta_time) override;
	//TODO:draw_guiからdrawに変更
	virtual void draw_gui() const override;
	bool is_end() const;

private:
	float timer_{ 0.0f };
	bool is_end_{ false };
};

#endif//!CLEAR_IAMGE_H_

