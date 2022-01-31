#ifndef PAUSE_SCENE_H_
#define PAUSE_SCENE_H_

#include "IScene.h"
class PauseScene : public IScene
{
public:
	virtual void start() override;
	virtual void update(float delta_time) override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool is_end() const override;
	virtual const std::string next() const override;

private:
	int selection_id_{ 0 };
	bool is_end_{ true };
};
#endif//!PAUSE_SCENE_H_

