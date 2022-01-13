#ifndef TUTORIAL_SCENE_H_
#define TUTORIAL_SCENE_H_

#include "IScene.h"
#include <GSgame.h>

//操作やゲーム性の説明を表示するシーン
class TutorialScene : public IScene
{
public:
	virtual void start() override;
	virtual void update(float delta_time) override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool is_end() const override;
	virtual const std::string next() const override;
private:
	//シーンを抜ける
	void exit();
	//ページを変える
	void turn_page();
	//ページをスクロールする
	void scroll_page(float delta_time);
	//操作説明ページへスクロール
	void scroll_control(float delta_time);
	//ヒントページへスクロール
	void scroll_hint(float delta_time);

private:
	int page_; //ページ番号
	float scroll_speed_;
	GSvector2 position_board_;
	bool is_end_;

};
#endif//!TUTORIAL_SCENE_H_
