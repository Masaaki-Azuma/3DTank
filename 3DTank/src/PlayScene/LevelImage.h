#ifndef LEVEL_IMAGE_H_
#define LEVEL_IMAGE_H_

#include "Util/NumberTexture.h"

//レベル情報演出を管理するクラス。ミニシーン
class LevelImage
{
public:
	LevelImage();
	//初期化
	void initialize(int level);
	void update(float delta_time);
	void draw() const;
	//終了したか？
	bool is_end() const;

private:
	float timer_{ 0.0f };
	bool is_end_{ false };
	NumberTexture number_;
	int level_{ -1 };
};
#endif//!LEVEL_IMAGE_H_

