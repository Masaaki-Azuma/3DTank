#include "TitleScene.h"
#include <gslib.h>
#include "Assets.h"

void TitleScene::start()
{
	//ForDebug
	//終了フラグの初期化
	is_end_ = false;
	//!ForDebug
	//リソースの読み込み
	gsLoadTexture(Texture_TitleLogo, "Assets/title_logo.png");
	gsLoadTexture(Texture_PressZ, "Assets/press_z.png");
}

void TitleScene::update(float delta_time)
{
	//ForDebug
	//zキーでシーン遷移
	if (gsGetKeyTrigger(GKEY_Z)) {
		is_end_ = true;
	}
	//!ForDebug
}

void TitleScene::draw() const
{
	//タイトルロゴを表示
	GSvector2 position_title{ 0, 0 };
	gsDrawSprite2D(Texture_TitleLogo, &position_title, NULL, NULL, NULL, NULL, NULL);
	//「キーを押してスタート」を表示
	GSvector2 position_pressZ{ 0, 200 };
	gsDrawSprite2D(Texture_PressZ, &position_pressZ, NULL, NULL, NULL, NULL, NULL);
}

void TitleScene::end()
{
	//リソースの解放
	gsDeleteTexture(Texture_TitleLogo);
	gsDeleteTexture(Texture_PressZ);
}

bool TitleScene::is_end() const
{
	return is_end_;
}

const std::string TitleScene::next() const
{
	return "PlayScene";
}
