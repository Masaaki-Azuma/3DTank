#ifndef FADE_H_
#define FADE_H_

#include <gslib.h>

//
class Fade
{
private:
	enum class State
	{
		FadeOut,
		Hiding,
		FadeIn,
		Opening
	};
public:
	Fade(GSuint texture);
	void update(float delta_time);
	void draw() const;
	void fade_out();
	void fade_in();
	bool is_hiding() const;
	bool is_opening() const;
	bool is_running() const;
private:
	void update_fade_out(float delta_time);
	void update_fade_in(float delta_time);

private:
	State state_;
	GSrect rect_;
};
#endif//!FADE_H_

