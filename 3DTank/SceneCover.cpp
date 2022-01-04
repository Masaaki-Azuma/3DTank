#include "SceneCover.h"
#include "Assets.h"

const int ImageHeight{ 1200 };    //シーンを隠す画像の高さ
const float ScrollSpeed{ 30.0f }; //シーン遷移の速さ

SceneCover::SceneCover():
	state_{ State::Opened },
	position_{ 0.0f, -1200 }
{
}

void SceneCover::update(float delta_time)
{
	//HACK:関数ポインタで簡潔に書けるらしい
	//状態によって分岐
	switch (state_) {
	case State::Closing: update_close(delta_time); break;
	case State::Opening: update_open(delta_time);  break;
	default:            /*何もしない*/             break;
	}
}

void SceneCover::draw() const
{
	gsDrawSprite2D(Texture_RedCurtain, &position_, NULL, NULL, NULL, NULL, NULL);
}

void SceneCover::close()
{
	state_ = State::Closing;
}

void SceneCover::open()
{
	state_ = State::Opening;
}

bool SceneCover::is_running() const
{
	return state_ == State::Closing || state_ == State::Opening;
}

bool SceneCover::is_closed() const
{
	return state_ == State::Closed;
}

bool SceneCover::is_opened() const
{
	return state_ == State::Opened;
}

void SceneCover::update_close(float delta_time)
{
	//閉じる
	position_.y += ScrollSpeed * delta_time;
	//閉じ終わったか？
	if (position_.y >= 0.0f) {
		position_.y = 0.0f;
		state_ = State::Closed;
	}
}

void SceneCover::update_open(float delta_time)
{
	//開ける
	position_.y -= ScrollSpeed * delta_time;
	//閉じ終わったか？
	if (position_.y <= -ImageHeight) {
		position_.y = -ImageHeight;
		state_ = State::Opened;
	}
}
