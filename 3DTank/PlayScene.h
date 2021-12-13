#ifndef PLAY_SCENE_H_
#define PLAY_SCENE_H_

#include "IScene.h"
#include "World.h"

class PlayScene : public IScene
{
private:
    

public:
    virtual void start() override;
    virtual void update(float delta_time) override;
    virtual void draw() const override;
    virtual void end() override;

    //シーンが終了したか？
    virtual bool is_end() const override;
    //次のシーン名を取得
    virtual const std::string next() const override;
private:
    void update_introduction(float delta_time);
    void update_battle(float delta_time);
    void update_stage_clear(float delta_time);

private:
    World world_;
    int state_;
};
#endif//!PLAY_SCENE_H_

