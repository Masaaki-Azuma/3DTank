#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include "IScene.h"
class TitleScene : public IScene
{
    //�V�[���J�n����
    virtual void start() override;
    //�V�[���̍X�V
    virtual void update(float delta_time) override;
    //�V�[���̕`��
    virtual void draw() const override;
    //�V�[���̏I������
    virtual void end() override;
};
#endif//!TITLE_SCENE_H_

