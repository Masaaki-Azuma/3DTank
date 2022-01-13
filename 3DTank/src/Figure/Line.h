#ifndef LINE_H_
#define LINE_H_

#include <gslib.h>

//�����f�[�^��ێ�����N���X
class Line
{
public:
	Line(const GSvector3& start, const GSvector3& end);
	const GSvector3& start() const;
	const GSvector3& end() const;
private:
	GSvector3 start_;
	GSvector3 end_;
};
#endif//!LINE_H_

