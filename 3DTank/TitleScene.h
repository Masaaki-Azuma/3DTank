#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include "IScene.h"

//�^�C�g���V�[��
class TitleScene : public IScene
{
public:
    //�V�[���J�n����
    virtual void start() override;
    //�V�[���̍X�V
    virtual void update(float delta_time) override;
    //�V�[���̕`��
    virtual void draw() const override;
    //�V�[���̏I������
    virtual void end() override;
    //�V�[�����I���������H
    virtual bool is_end() const override;
    //���̃V�[�������擾
    virtual const std::string next() const override;

private:
    bool is_end_;
};
#endif//!TITLE_SCENE_H_

