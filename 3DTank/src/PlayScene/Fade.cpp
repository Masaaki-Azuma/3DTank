#include "Fade.h"
#include "Screen.h"
#include "Assets.h"
#include "Sound.h"

const float FadeSpeed{ 40.0f };

Fade::Fade(GSuint texture):
	state_{State::Opening},
	rect_{0.0f, 0.0f, Screen::Width, Screen::Height}
{
}

void Fade::update(float delta_time)
{
	switch (state_) {
	case State::FadeOut: update_fade_out(delta_time); break;
	case State::FadeIn:  update_fade_in(delta_time);  break;
	default:             /*‰½‚à‚µ‚È‚¢*/               break;
	}
}

void Fade::draw() const
{
	GSvector2 position{ rect_.left, 0.0f };
	gsDrawSprite2D(Texture_SilhouetteBackground, &position, &rect_, NULL, NULL, NULL, NULL);
}

void Fade::fade_out()
{
	rect_.right = Screen::Width;
	rect_.left = Screen::Width;
	state_ = State::FadeOut;
}

void Fade::fade_in()
{
	rect_.left = 0.0f;
	state_ = State::FadeIn;
}

bool Fade::is_hiding() const
{
	return state_ == State::Hiding;
}

bool Fade::is_opening() const
{
	return state_ == State::Opening;
}

bool Fade::is_running() const
{
	return state_ == State::FadeOut || state_ == State::FadeIn;
}

void Fade::update_fade_out(float delta_time)
{
	rect_.left -= FadeSpeed * delta_time;
	if (rect_.left < 0.0f) {
		state_ = State::Hiding;
	}
}

void Fade::update_fade_in(float delta_time)
{
	rect_.right -= FadeSpeed * delta_time;
	if (rect_.right < 0.0f) {
		
		state_ = State::Opening;
	}
}
