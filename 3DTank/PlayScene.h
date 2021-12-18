#ifndef PLAY_SCENE_H_
#define PLAY_SCENE_H_

#include "IScene.h"
#include "World.h"
#include "ActorGenerator.h"
#include "ClearImage.h"
#include "LevelImage.h"

//���C���Q�[���v���C�V�[���N���X
//�V�[���̍X�V�A�`��A����у������̊m�ہE������Ǘ�����
class PlayScene : public IScene
{

public:
    virtual void start() override;
    virtual void update(float delta_time) override;
    virtual void draw() const override;
    virtual void end() override;

    //�V�[�����I���������H
    virtual bool is_end() const override;
    //���̃V�[�������擾
    virtual const std::string next() const override;

private:
    void update_introduction(float delta_time);
    void update_battle(float delta_time);
    void update_level_clear(float delta_time);

private:

private:
    enum State //�V�[�����J�ڏ��
    {
        Introduction,
        Battle,
        LevelClear,
    };
    World world_;
    State state_;
    LevelImage level_image_;
    ClearImage clear_image_;

    int level_;

};
#endif//!PLAY_SCENE_H_

