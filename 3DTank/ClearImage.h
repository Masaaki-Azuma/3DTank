#ifndef CLEAR_IAMGE_H_
#define CLEAR_IAMGE_H_

//�N���A���o���Ǘ�����N���X�B�~�j�V�[��
class ClearImage
{
public:
	void initialize();
	void update(float delta_time);
	void draw() const;
	bool is_end() const;

private:
	float timer_{ 0.0f };
	bool is_end_{ false };
};

#endif//!CLEAR_IAMGE_H_

