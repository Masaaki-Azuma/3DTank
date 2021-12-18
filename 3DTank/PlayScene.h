#ifndef PLAY_SCENE_H_
#define PLAY_SCENE_H_

#include "IScene.h"
#include "World.h"
#include "ActorGenerator.h"
#include "ClearImage.h"
#include "LevelImage.h"

//メインゲームプレイシーンクラス
//シーンの更新、描画、およびメモリの確保・解放を管理する
class PlayScene : public IScene
{

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
    void update_level_clear(float delta_time);

private:

private:
    enum State //シーン内遷移状態
    {
        Introduction,
        Battle,
        LevelClear,
    };
    World world_;
    State state_;
    LevelImage level_image_;
    ClearImage clear_image_;

    int level_;

};
#endif//!PLAY_SCENE_H_

