#include "Line.h"

Line::Line(const GSvector3& start, const GSvector3& end):
    start_{start}, end_{end}
{
}

const GSvector3& Line::start() const
{
    return start_;
}

const GSvector3& Line::end() const
{
    return end_;
}
