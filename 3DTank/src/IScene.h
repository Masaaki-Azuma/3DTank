#ifndef ISCENE_H_
#define ISCENE_H_

#include <string>

//�V�[�����ۃC���^�[�t�F�[�X
class IScene
{
public:
	virtual ~IScene() = default;
	virtual void start() = 0;
	virtual void update(float delta_time) = 0;
	virtual void draw() const = 0;
	virtual void end() = 0;

	//�V�[�����I���������H
	virtual bool is_end() const = 0;
	//���̃V�[�������擾
	virtual const std::string next() const = 0;
};

#endif//!ISCENE_H_