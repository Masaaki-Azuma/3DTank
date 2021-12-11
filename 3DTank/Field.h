#ifndef FIELD_H_
#define FIELD_H_

#include <gslib.h>

class BoundingSphere;

//地形情報を管理するクラス
class Field
{
public:
	Field(GSuint mesh, GSuint collider);

	bool collide(const BoundingSphere& sphere, GSvector3* center = nullptr);
private:
	//地形メッシュオクツリー
	GSuint mesh_;
	//地形コライダーオクツリー
	GSuint collider_;
};
#endif//!FIELD_H_

