#ifndef PLAY_SCENE_H_
#define PLAY_SCENE_H_

#include "IScene.h"
#include "World.h"
#include "ClearImage.h"
#include "LevelImage.h"
#include "Fade.h"

//メインゲームプレイシーンクラス
//シーンの更新、描画、およびメモリの確保・解放を管理する
class PlayScene : public IScene
{
private:
    enum class State //シーン内遷移状態
    {
        Introduction,
        Battle,
        LevelClear,
    };

public:
    PlayScene();
    virtual void start() override;
    virtual void update(float delta_time) override;
    virtual void draw() const override;
    virtual void end() override;
    //シーンが終了したか？
    virtual bool is_end() const override;
    //次のシーン名を取得
    virtual const std::string next() const override;
private:
    //ステージ開始画面更新
    void update_introduction(float delta_time);
    //戦闘画面更新
    void update_battle(float delta_time);
    //ステージクリア画面更新
    void update_level_clear(float delta_time);

private:
    //ワールド
    World world_;
    //レベル情報演出
    LevelImage level_image_;
    //クリア演出
    ClearImage clear_image_;
    //フェード演出
    Fade fade_;
    //画面状態
    State state_;
    //現在ステージ番号
    int level_;

};
#endif//!PLAY_SCENE_H_

