#ifndef TUTORIAL_SCENE_H_
#define TUTORIAL_SCENE_H_

#include "IScene.h"
#include <GSgame.h>

//�����Q�[�����̐�����\������V�[��
class TutorialScene : public IScene
{
public:
	virtual void start() override;
	virtual void update(float delta_time) override;
	virtual void draw() const override;
	virtual void end() override;
	virtual bool is_end() const override;
	virtual const std::string next() const override;
private:
	//�V�[���𔲂���
	void exit();
	//�y�[�W��ς���
	void turn_page();
	//�y�[�W���X�N���[������
	void scroll_page(float delta_time);
	//��������y�[�W�փX�N���[��
	void scroll_control(float delta_time);
	//�q���g�y�[�W�փX�N���[��
	void scroll_hint(float delta_time);

private:
	int page_; //�y�[�W�ԍ�
	float scroll_speed_;
	GSvector2 position_board_;
	bool is_end_;

};
#endif//!TUTORIAL_SCENE_H_
