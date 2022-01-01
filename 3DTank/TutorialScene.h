#ifndef TUTORIAL_SCENE_H_
#define TUTORIAL_SCENE_H_

#include "IScene.h"

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
	bool is_end_;
};
#endif//!TUTORIAL_SCENE_H_
