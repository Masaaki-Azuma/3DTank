#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include "IScene.h"
#include <gslib.h>

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
    //�I�����ύX
    void select_menu();
    //�I��������
    void confirm_menu();

    //�摜���ȒP�ɕ`��
    void draw_2Dsprite(GSuint texture_id, const GSvector2& position = { 0, 0 }, const GSrect source_rect = GSrect{0, 0, 0, 0}) const;
private:
    bool is_end_;
    int selection_id_;
};
#endif//!TITLE_SCENE_H_

