#include "TutorialScene.h"
#include <gslib.h>

void TutorialScene::start()
{
    is_end_ = false;
}

void TutorialScene::update(float delta_time)
{
}

void TutorialScene::draw() const
{
    gsDrawText("チュートリアルシーン");
}

void TutorialScene::end()
{
}

bool TutorialScene::is_end() const
{
    return is_end_;
}

const std::string TutorialScene::next() const
{
    return "TitleScene";
}
