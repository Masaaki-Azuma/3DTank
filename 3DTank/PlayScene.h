#ifndef PLAY_SCENE_H_
#define PLAY_SCENE_H_

#include "IScene.h"
#include "World.h"
#include "ClearImage.h"
#include "LevelImage.h"
#include "Fade.h"

//���C���Q�[���v���C�V�[���N���X
//�V�[���̍X�V�A�`��A����у������̊m�ہE������Ǘ�����
class PlayScene : public IScene
{
private:
    enum class State //�V�[�����J�ڏ��
    {
        Introduction,
        Battle,
        LevelClear,
    };

public:
    PlayScene();
    virtual void start() override;
    virtual void update(float delta_time) override;
    virtual void draw() const override;
    virtual void end() override;
    //�V�[�����I���������H
    virtual bool is_end() const override;
    //���̃V�[�������擾
    virtual const std::string next() const override;
private:
    //�X�e�[�W�J�n��ʍX�V
    void update_introduction(float delta_time);
    //�퓬��ʍX�V
    void update_battle(float delta_time);
    //�X�e�[�W�N���A��ʍX�V
    void update_level_clear(float delta_time);

private:
    //���[���h
    World world_;
    //���x����񉉏o
    LevelImage level_image_;
    //�N���A���o
    ClearImage clear_image_;
    //�t�F�[�h���o
    Fade fade_;
    //��ʏ��
    State state_;
    //���݃X�e�[�W�ԍ�
    int level_;

};
#endif//!PLAY_SCENE_H_

