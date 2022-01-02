#include "TutorialScene.h"
#include <gslib.h>
#include "Assets.h"

void TutorialScene::start()
{
    gsLoadTexture(Texture_Background, "Assets/background.png");
    gsLoadTexture(Texture_Tutorial_Board0, "Assets/tutorial_boardControl.png");
    gsLoadTexture(Texture_Tutorial_PressXToTitle, "Assets/tutorial_press_x_to_title.png");
    is_end_ = false;
}

void TutorialScene::update(float delta_time)
{
    //èIóπèàóù
    if (gsGetKeyTrigger(GKEY_X)) {
        is_end_ = true;
    }
}

void TutorialScene::draw() const
{
    //îwåiÇï`âÊ
    static const GSvector2 position_background{ 0, 0 };
    gsDrawSprite2D(Texture_Background, &position_background, NULL, NULL, NULL, NULL, NULL);

    //ê‡ñæ1Çï`âÊ
    static const GSvector2 position_board{ 70, 60 };
    gsDrawSprite2D(Texture_Tutorial_Board0, &position_background, NULL, NULL, NULL, NULL, NULL);
    static const GSvector2 position_pressX{ 50, 970 };
    gsDrawSprite2D(Texture_Tutorial_PressXToTitle, &position_pressX, NULL, NULL, NULL, NULL, NULL);
}

void TutorialScene::end()
{
    gsDeleteTexture(Texture_Background);
    gsDeleteTexture(Texture_Tutorial_Board0);
}

bool TutorialScene::is_end() const
{
    return is_end_;
}

const std::string TutorialScene::next() const
{
    return "TitleScene";
}
