#ifndef SCENE_COVER_H_
#define SCENE_COVER_H_

#include <GSgame.h>

//�V�[���؂�ւ����̉��o���Ǘ�����N���X
class SceneCover
{
private:
	enum class State
	{
		Opened,  //��������
		Closing, //�B����
		Closed,  //�B������
		Opening, //������
	};
public:
	SceneCover();
	void update(float delta_time);
	void draw() const;
	//�V�[�����B���n�߂�
	void close();
	//�V�[���������n�߂�
	void open();
	//�V�[���J�ډ��o�����H
	bool is_running() const;
	//�V�[���͉B���I��������H
	bool is_closed() const;
	//�V�[���͌����I��������H
	bool is_opened() const;
private:
	void update_close(float delta_time);
	void update_open(float delta_time);

private:
	State state_;
	GSvector2 position_;
};
#endif//!SCENE_COVER_H_

