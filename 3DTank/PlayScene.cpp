#include "PlayScene.h"
#include <gslib.h>

void PlayScene::start()
{
	gsLoadTexture(0, "Assets/test.png");
}

void PlayScene::update(float delta_time)
{
}

void PlayScene::draw() const
{
	gsDrawSprite2D(0, NULL, NULL, NULL, NULL, NULL, 0.0f);
}

void PlayScene::end()
{
}
