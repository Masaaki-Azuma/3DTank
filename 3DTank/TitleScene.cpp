#include "TitleScene.h"
#include <gslib.h>
#include "Assets.h"

void TitleScene::start()
{
	//リソースの読み込み
	gsLoadTexture(Texture_TitleLogo, "Assets/title_logo.png");
	gsLoadTexture(Texture_PressZ, "Assets/press_z.png");
}

void TitleScene::update(float delta_time)
{
}

void TitleScene::draw() const
{
	GSvector2 position_title{ 0, 0 };
	gsDrawSprite2D(Texture_TitleLogo, &position_title, NULL, NULL, NULL, NULL, NULL);
	GSvector2 position_pressZ{ 0, 200 };
	gsDrawSprite2D(Texture_PressZ, &position_pressZ, NULL, NULL, NULL, NULL, NULL);
}

void TitleScene::end()
{
	//リソースの解放
	gsDeleteTexture(Texture_TitleLogo);
	gsDeleteTexture(Texture_PressZ);
}
