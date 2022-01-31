#include "TitleScene.h"
#include <stdexcept>
#include <GSmusic.h>
#include "Assets.h"
#include "Sound.h"

enum //次の遷移シーン
{
	GameStart = 0,
	Tutorial = 1,
};

const int MaxSelection{ 2 }; //選択肢の個数

void TitleScene::start()
{
	//リソースの読み込み
	gsLoadTexture(Texture_Title_Logo, "Assets/Texture/title_logo.png");
	gsLoadTexture(Texture_Background, "Assets/Texture/background.png");
	gsLoadTexture(Texture_Title_Menu, "Assets/Texture/title_menuText.png");
	gsLoadTexture(Texture_Cursor, "Assets/Texture/title_cursor.png");

	gsLoadSE(Se_CursorMove, "Assets/Sound/SE/cursor_move.wav", 1, GWAVE_DEFAULT);
	//gsLoadMusic(Music_Title, "Assets/Sound/BGM/title.mp3", GS_TRUE);
	gsLoadMusic(Music_Title, "Assets/Sound/BGM/title_Movie.mp3", GS_TRUE);
	//終了フラグの初期化
	is_end_ = false;
	//選択肢番号を初期化
	selection_id_ = 0;
	//BGMのバインド
	gsBindMusic(Music_Title);
	//BGMの再生
	gsPlayMusic();
}

void TitleScene::update(float delta_time)
{
	confirm_menu();
	select_menu();
}

void TitleScene::draw() const
{
	//背景を描画
	draw_2Dsprite(Texture_Background);
	//タイトルロゴを表示
	draw_2Dsprite(Texture_Title_Logo, GSvector2{ 150, 130 });

	//選択肢を描画
	static const int selection_top{ 540 };
	static const int selection_gap{ 200 };
	draw_2Dsprite(Texture_Title_Menu, GSvector2{ 540, selection_top                     }, GSrect{ 0, 0, 720, 120 });
	draw_2Dsprite(Texture_Title_Menu, GSvector2{ 540, selection_top + selection_gap     }, GSrect{ 0, 120, 720, 240 });
	//カーソルを描画
	draw_2Dsprite(Texture_Cursor, GSvector2{ 400, selection_top + (GSfloat)selection_gap * selection_id_ });
}

void TitleScene::end()
{
	//BGMの停止
	gsStopMusic();
	//リソースの解放
	gsDeleteTexture(Texture_Title_Logo);
	gsDeleteTexture(Texture_Background);
	gsDeleteTexture(Texture_Title_Menu);
	gsDeleteTexture(Texture_Cursor);

	gsDeleteSE(Se_CursorMove);
	gsDeleteMusic(Music_Title);
}

bool TitleScene::is_end() const
{
	return is_end_;
}

const std::string TitleScene::next() const
{
	switch (selection_id_) {
	case GameStart: return "PlayScene";     break;
	case Tutorial:  return "TutorialScene"; break;
	default:
		throw std::runtime_error("タイトルシーンからの不正な遷移です");
		break;
	}
}

void TitleScene::select_menu()
{
	//上下キーでカーソル移動
	if (gsGetKeyTrigger(GKEY_DOWN)) {
		selection_id_ += 1;
		gsPlaySE(Se_CursorMove);
	}
	else if (gsGetKeyTrigger(GKEY_UP)) {
		selection_id_ += MaxSelection - 1;
		gsPlaySE(Se_CursorMove);
	}
	//選択肢番号を選択肢数に応じてループ調整
	selection_id_ %= MaxSelection;
}

void TitleScene::confirm_menu()
{
	//zキーでシーン遷移
	if (gsGetKeyTrigger(GKEY_Z)) {
		is_end_ = true;
	}
}

void TitleScene::draw_2Dsprite(GSuint texture_id, const GSvector2& position, const GSrect source_rect) const
{
	//画像の一部を切り出しているか？
	bool is_clipped = !(
		source_rect.left   == 0 &&
		source_rect.top    == 0 &&
		source_rect.right  == 0 &&
		source_rect.bottom == 0);

	if (is_clipped) {
		gsDrawSprite2D(texture_id, &position, &source_rect, NULL, NULL, NULL, NULL);
	}
	else {
		gsDrawSprite2D(texture_id, &position, NULL, NULL, NULL, NULL, NULL);
	}
}
