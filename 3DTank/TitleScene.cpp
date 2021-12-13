#include "TitleScene.h"
#include <gslib.h>
#include "Assets.h"

void TitleScene::start()
{
	//リソースの読み込み
	gsLoadTexture(Texture_TitleLogo, "Assets/title_logo.png");
	gsLoadTexture(Texture_PressZ, "press_z.png");
}

void TitleScene::update(float delta_time)
{
}

void TitleScene::draw() const
{
	gsDrawSprite2D(Texture_TitleLogo, &GSvector2{ 0, 0 }, NULL, NULL, NULL, NULL, NULL);
	gsDrawSprite2D(Texture_PressZ, &GSvector2{ 0, 200 }, NULL, NULL, NULL, NULL, NULL);
}

void TitleScene::end()
{
	//リソースの解放
	gsDeleteTexture(Texture_TitleLogo);
	gsDeleteTexture(Texture_PressZ);
}
