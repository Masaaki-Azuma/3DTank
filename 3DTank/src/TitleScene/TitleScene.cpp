#include "TitleScene.h"
#include <stdexcept>
#include "Assets.h"

enum //���̑J�ڃV�[��
{
	GameStart = 0,
	Tutorial = 1,
};

const int MaxSelection{ 2 }; //�I�����̌�

void TitleScene::start()
{
	//ForDebug
	//�I���t���O�̏�����
	is_end_ = false;
	//!ForDebug
	//�I�����ԍ���������
	selection_id_ = 0;

	//���\�[�X�̓ǂݍ���
	gsLoadTexture(Texture_Title_Logo, "Assets/title_logo.png");
	gsLoadTexture(Texture_Background, "Assets/background.png");
	gsLoadTexture(Texture_Title_Menu, "Assets/title_menuText.png");
	gsLoadTexture(Texture_PressZ, "Assets/press_z.png");
	gsLoadTexture(Texture_Cursor, "Assets/title_cursor.png");
}

void TitleScene::update(float delta_time)
{
	confirm_menu();
	select_menu();
}

void TitleScene::draw() const
{
	//�w�i��`��
	draw_2Dsprite(Texture_Background);
	//�^�C�g�����S��\��
	draw_2Dsprite(Texture_Title_Logo, GSvector2{ 150, 130 });

	//�I������`��
	static const int selection_top{ 540 };
	static const int selection_gap{ 200 };
	draw_2Dsprite(Texture_Title_Menu, GSvector2{ 540, selection_top                     }, GSrect{ 0, 0, 720, 120 });
	draw_2Dsprite(Texture_Title_Menu, GSvector2{ 540, selection_top + selection_gap     }, GSrect{ 0, 120, 720, 240 });
	//�J�[�\����`��
	draw_2Dsprite(Texture_Cursor, GSvector2{ 400, selection_top + (GSfloat)selection_gap * selection_id_ });
}

void TitleScene::end()
{
	//���\�[�X�̉��
	gsDeleteTexture(Texture_Title_Logo);
	gsDeleteTexture(Texture_Background);
	gsDeleteTexture(Texture_Title_Menu);
	gsDeleteTexture(Texture_PressZ);
	gsDeleteTexture(Texture_Cursor);
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
		throw std::runtime_error("�^�C�g���V�[������̕s���ȑJ�ڂł�");
		break;
	}
}

void TitleScene::select_menu()
{
	//�㉺�L�[�ŃJ�[�\���ړ�
	if (gsGetKeyTrigger(GKEY_DOWN)) {
		selection_id_ += 1;
	}
	else if (gsGetKeyTrigger(GKEY_UP)) {
		selection_id_ += MaxSelection - 1;
	}
	//�I�����ԍ���I�������ɉ����ă��[�v����
	selection_id_ %= MaxSelection;
}

void TitleScene::confirm_menu()
{
	//z�L�[�ŃV�[���J��
	if (gsGetKeyTrigger(GKEY_Z)) {
		is_end_ = true;
	}
}

void TitleScene::draw_2Dsprite(GSuint texture_id, const GSvector2& position, const GSrect source_rect) const
{
	//�摜�̈ꕔ��؂�o���Ă��邩�H
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
