#ifndef LEVEL_IMAGE_H_
#define LEVEL_IMAGE_H_

//���x����񉉏o���Ǘ�����N���X�B�~�j�V�[��
class LevelImage
{
public:
	//������
	void initialize();
	void update(float delta_time);
	void draw() const;
	//�I���������H
	bool is_end() const;

private:
	float timer_{ 0.0f };
	bool is_end_{ false };
};
#endif//!LEVEL_IMAGE_H_

