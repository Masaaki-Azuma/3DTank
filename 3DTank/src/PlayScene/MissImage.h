#ifndef MISS_IMAGE_H_
#define MISS_IMAGE_H_

#include <GSgame.h>

//HACK:他のミニシーンと処理かぶり
//ステージミス演出クラス
class MissImage
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
	GSvector2 position_{ 0.0f, 0.0f };
	GSvector2 velocity_{ 0.0f, 0.0f };
};
#endif//!MISS_IMAGE_H_

