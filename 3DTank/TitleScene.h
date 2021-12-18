#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include "IScene.h"

//タイトルシーン
class TitleScene : public IScene
{
public:
    //シーン開始処理
    virtual void start() override;
    //シーンの更新
    virtual void update(float delta_time) override;
    //シーンの描画
    virtual void draw() const override;
    //シーンの終了処理
    virtual void end() override;
    //シーンが終了したか？
    virtual bool is_end() const override;
    //次のシーン名を取得
    virtual const std::string next() const override;

private:
    bool is_end_;
};
#endif//!TITLE_SCENE_H_

