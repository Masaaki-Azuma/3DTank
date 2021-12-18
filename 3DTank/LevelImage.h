#ifndef LEVEL_IMAGE_H_
#define LEVEL_IMAGE_H_

//レベル情報演出を管理するクラス。ミニシーン
class LevelImage
{
public:
	void initialize();
	void update(float delta_time);
	void draw() const;
	bool is_end() const;

private:
	float timer_{ 0.0f };
	bool is_end_{ false };
};
#endif//!LEVEL_IMAGE_H_

