#ifndef SCENE_COVER_H_
#define SCENE_COVER_H_

#include <GSgame.h>

//シーン切り替え時の演出を管理するクラス
class SceneCover
{
private:
	enum class State
	{
		Opened,  //見せ完了
		Closing, //隠し中
		Closed,  //隠し完了
		Opening, //見せ中
	};
public:
	SceneCover();
	void update(float delta_time);
	void draw() const;
	//シーンを隠し始める
	void close();
	//シーンを見せ始める
	void open();
	//シーン遷移演出中か？
	bool is_running() const;
	//シーンは隠し終わったか？
	bool is_closed() const;
	//シーンは見せ終わったか？
	bool is_opened() const;
private:
	void update_close(float delta_time);
	void update_open(float delta_time);

private:
	State state_;
	GSvector2 position_;
};
#endif//!SCENE_COVER_H_

