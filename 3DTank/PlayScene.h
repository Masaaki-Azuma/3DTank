#ifndef PLAY_SCENE_H_
#define PLAY_SCENE_H_

#include "IScene.h"
#include "World.h"

class PlayScene : public IScene
{
public:
    virtual void start() override;
    virtual void update(float delta_time) override;
    virtual void draw() const override;
    virtual void end() override;

private:
    World world_;
};
#endif//!PLAY_SCENE_H_

