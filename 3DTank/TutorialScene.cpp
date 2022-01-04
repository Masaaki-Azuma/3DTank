#include "TutorialScene.h"
#include <stdexcept>
#include "Assets.h"

const float ScrollSpeed{ 40.0f };
const int MaxPage{ 2 };
const int ScreenWidth{ 1920 };

enum Page //ページを表す状態変数
{
    Control,
    Hint,
};

void TutorialScene::start()
{
    gsLoadTexture(Texture_Background, "Assets/background.png");
    gsLoadTexture(Texture_Tutorial_Board0, "Assets/tutorial_boardControl.png");
    gsLoadTexture(Texture_Tutorial_Board1, "Assets/tutorial_boardHint.png");
    gsLoadTexture(Texture_Tutorial_PressXToTitle, "Assets/tutorial_press_x_to_title.png");
    page_ = Control;
    position_board_ = GSvector2{ 0.0f, 0.0f };
    scroll_speed_ = 0.0f;
    is_end_ = false;
}

void TutorialScene::update(float delta_time)
{
    //ページを変える操作
    turn_page();
    //ページをスクロールする
    scroll_page(delta_time);

    //ページ移動中ならここで更新終了
    if (scroll_speed_ != 0.0f) return;
    //シーンを抜ける操作
    exit();
}

void TutorialScene::draw() const
{
    //背景を描画
    static const GSvector2 position_background{ 0, 0 };
    gsDrawSprite2D(Texture_Background, &position_background, NULL, NULL, NULL, NULL, NULL);

    //説明1を描画
    GSvector2 position_board1 = position_board_;
    gsDrawSprite2D(Texture_Tutorial_Board0, &position_board1, NULL, NULL, NULL, NULL, NULL);
    //説明2を描画
    GSvector2 position_board2 = position_board_ + GSvector2{ 1920, 0 };
    gsDrawSprite2D(Texture_Tutorial_Board1, &position_board2, NULL, NULL, NULL, NULL, NULL);

    //ページ移動中ならここで描画終了
    if (scroll_speed_ != 0.0f) return;

    //「タイトルへ」文字列を描画
    static const GSvector2 position_pressX{ 50, 970 };
    gsDrawSprite2D(Texture_Tutorial_PressXToTitle, &position_pressX, NULL, NULL, NULL, NULL, NULL);

    //HACK:インデントはこれでいいのか？
    //カーソルを描画
    static const GSvector2 scaling{ 0.8f, 0.8f };
    switch (page_) {
    case Control: {
        static const GSvector2 position_right_cursor{ 1800, 470 };
        gsDrawSprite2D(Texture_Cursor, &position_right_cursor, NULL, NULL, NULL, &scaling, NULL);
        break;
    }
    case Hint: {
        static const GSvector2 position_left_cursor{ 60, 530 };
        static const GSvector2 center{ 60, 60 };
        gsDrawSprite2D(Texture_Cursor, &position_left_cursor, NULL, &center, NULL, &scaling, 180.0f);
        break;
    }
    }
}

void TutorialScene::end()
{
    gsDeleteTexture(Texture_Background);
    gsDeleteTexture(Texture_Tutorial_Board0);
    gsDeleteTexture(Texture_Tutorial_Board1);
    gsDeleteTexture(Texture_Tutorial_PressXToTitle);
}

bool TutorialScene::is_end() const
{
    return is_end_;
}

const std::string TutorialScene::next() const
{
    return "TitleScene";
}

void TutorialScene::exit()
{
    //終了処理
    if (gsGetKeyTrigger(GKEY_X)) {
        is_end_ = true;
    }
}

void TutorialScene::turn_page()
{
    if (gsGetKeyTrigger(GKEY_RIGHT)) {
        scroll_speed_ = -ScrollSpeed;
        page_ = std::min(page_ + 1, MaxPage - 1);
    }
    else if (gsGetKeyTrigger(GKEY_LEFT)) {
        scroll_speed_ = ScrollSpeed;
        page_ = std::max(page_ - 1, 0);
    }
    position_board_.x += scroll_speed_;
}

void TutorialScene::scroll_page(float delta_time)
{
    switch (page_) {
    case Control: scroll_control(delta_time); break;
    case Hint:    scroll_hint(delta_time);    break;
    default:
        throw std::runtime_error("チュートリアルシーン内の不正な遷移です");
        break;
    }
}

void TutorialScene::scroll_control(float delta_time)
{
    if (position_board_.x >= 0) {
        position_board_.x = 0;
        scroll_speed_ = 0.0f;
    }
}

void TutorialScene::scroll_hint(float delta_time)
{
    if (position_board_.x <= -ScreenWidth) {
        position_board_.x = -ScreenWidth;
        scroll_speed_ = 0.0f;
    }
}
