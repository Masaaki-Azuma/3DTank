#ifndef NULL_SCENE_H_
#define NULL_SCENE_H_

#include "IScene.h"

//何もしないシーン【ヌルパターン】
class NullScene : public IScene
{
public:
	virtual void start() override {}
	virtual void update(float delta_time) override {}
	virtual void draw() const override {}
	virtual void end() override {}
	virtual bool is_end() const override { return false; }
	virtual const std::string next() const override { return "NullScene"; }
};
#endif//!NULL_SCENE_H_
