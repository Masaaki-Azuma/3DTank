#ifndef CLEAR_IAMGE_H_
#define CLEAR_IAMGE_H_

#include <GSgame.h>

//クリア演出を管理するクラス。ミニシーン
class ClearImage
{
public:
	//初期化
	void initialize();
	void update(float delta_time);
	void draw() const;
	//終了したか？
	bool is_end() const;

private:
	float timer_{ 0.0f };
	bool is_end_{ false };
	GSvector2 image_scale_{ 0.0f, 0.0f };
};

#endif//!CLEAR_IAMGE_H_

