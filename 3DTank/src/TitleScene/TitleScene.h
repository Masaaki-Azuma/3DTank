#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include "IScene.h"
#include <gslib.h>

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
    //選択肢変更
    void select_menu();
    //選択肢決定
    void confirm_menu();

    //画像を簡単に描画
    void draw_2Dsprite(GSuint texture_id, const GSvector2& position = { 0, 0 }, const GSrect source_rect = GSrect{0, 0, 0, 0}) const;
private:
    bool is_end_;
    int selection_id_;
};
#endif//!TITLE_SCENE_H_

