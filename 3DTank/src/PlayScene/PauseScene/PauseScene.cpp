#include "PauseScene.h"
#include <gslib.h>
#include <stdexcept>
#include "Screen.h"
#include "Assets.h"

const GSvector2 SizeBoard{ 900, 630 };
enum
{
    ReturnPlayScene = 0,
    TitleScene      = 1,
};

const int MaxSelection{ 2 };

void PauseScene::start()
{
    //���\�[�X�����[�h
    gsLoadTexture(Texture_Pause_Board, "Assets/pause_board.png");
    gsLoadTexture(Texture_Pause_ReturnToGame, "Assets/pause_returnGame.png");
    gsLoadTexture(Texture_Pause_ReturnToTitle, "Assets/pause_returnTitle.png");
    gsLoadTexture(Texture_Cursor, "Assets/title_cursor.png");
    selection_id_ = 0;
    is_end_ = false;
}

void PauseScene::update(float delta_time)
{
    //�|�[�Y��ʂ𔲂���
    if (gsGetKeyTrigger(GKEY_X)) {
        selection_id_ = 0;
        is_end_ = true;
        end();
    }

    //���j���[������
    if (gsGetKeyTrigger(GKEY_Z)) {
        is_end_ = true;
        end();
    }

    //���j���[��I��
    if (gsGetKeyTrigger(GKEY_DOWN)) {
        selection_id_ += 1;
    }
    else if (gsGetKeyTrigger(GKEY_UP)) {
        selection_id_ += MaxSelection - 1;
    }
    //�I�����ԍ���I�������ɉ����ă��[�v����
    selection_id_ %= MaxSelection;
}

void PauseScene::draw() const
{
    //��`��
    static const GSvector2 position_board{ Screen::Width / 2, Screen::Height / 2 };
    static const GSvector2 center_board{ SizeBoard / 2 };
    gsDrawSprite2D(Texture_Pause_Board, &position_board, NULL, &center_board, NULL, NULL, NULL);

    //�J�[�\����`��
    GSvector2 position_cursor{ 600, (float)340 + selection_id_ * 250 };
    gsDrawSprite2D(Texture_Cursor, &position_cursor, NULL, NULL, NULL, NULL, NULL);

    //�u�Q�[���֖߂�v��`��
    static const GSvector2 position_return_to_game{ 750, 350 };
    gsDrawSprite2D(Texture_Pause_ReturnToGame, &position_return_to_game, NULL, NULL, NULL, NULL, NULL);
    //�u�^�C�g���ցv��`��
    static const GSvector2 position_return_to_title{ 750, 600 };
    gsDrawSprite2D(Texture_Pause_ReturnToTitle, &position_return_to_title, NULL, NULL, NULL, NULL, NULL);
}

void PauseScene::end()
{
    //���\�[�X�����
    gsDeleteTexture(Texture_Pause_Board);
    gsDeleteTexture(Texture_Pause_ReturnToGame);
    gsDeleteTexture(Texture_Pause_ReturnToTitle);
}

bool PauseScene::is_end() const
{
    return is_end_;
}

const std::string PauseScene::next() const
{
    switch (selection_id_) {
    case ReturnPlayScene: return "PlayScene";
    case TitleScene:      return "TitleScene";
    default:
        throw std::runtime_error("�|�[�Y�V�[������̕s���ȑJ�ڂł�");
        break;
    }
}
