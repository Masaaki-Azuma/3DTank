#include "TitleScene.h"
#include <gslib.h>
#include "Assets.h"

void TitleScene::start()
{
	//ForDebug
	//�I���t���O�̏�����
	is_end_ = false;
	//!ForDebug
	//���\�[�X�̓ǂݍ���
	gsLoadTexture(Texture_TitleLogo, "Assets/title_logo.png");
	gsLoadTexture(Texture_PressZ, "Assets/press_z.png");
}

void TitleScene::update(float delta_time)
{
	//ForDebug
	//z�L�[�ŃV�[���J��
	if (gsGetKeyTrigger(GKEY_Z)) {
		is_end_ = true;
	}
	//!ForDebug
}

void TitleScene::draw() const
{
	//�^�C�g�����S��\��
	GSvector2 position_title{ 0, 0 };
	gsDrawSprite2D(Texture_TitleLogo, &position_title, NULL, NULL, NULL, NULL, NULL);
	//�u�L�[�������ăX�^�[�g�v��\��
	GSvector2 position_pressZ{ 0, 200 };
	gsDrawSprite2D(Texture_PressZ, &position_pressZ, NULL, NULL, NULL, NULL, NULL);
}

void TitleScene::end()
{
	//���\�[�X�̉��
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
