#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_

#include <gslib.h>

class BoundingSphere
{
public:
	BoundingSphere(float radius = 0.0f, const GSvector3& center = GSvector3{ 0.0f, 0.0f, 0.0f });
	//平行移動
	BoundingSphere translate(const GSvector3& position) const;
	//変換
	BoundingSphere transform(const GSmatrix4& matrix) const;
	//境界球同士の衝突判定
	bool intersects(const BoundingSphere& other) const;
	//デバッグ用境界球描画
	void draw() const;

	float radius() const;
	const GSvector3& center() const;
private:
	//半径
	float radius_;
	//中心座標(持ち主からの相対座標)
	GSvector3 center_;
};
#endif//!BOUNDING_SPHERE_H_

