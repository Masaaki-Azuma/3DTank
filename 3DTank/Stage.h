#ifndef STAGE_H_
#define STAGE_H_

#include <gslib.h>

class BoundingSphere;
class Line;

//ステージの管理クラス
//ステージデータの読み込み、解放、および地形との衝突判定を行う
class Stage
{
public:
	//コンストラクタ
	Stage(GSuint mesh, GSuint collider);
	~Stage();

	//TODO:loadやdrawがアクターにも使えるのはどうなの？

	//ステージの読み込み
	void load(int stage);
	//ステージの解放
	void clear();
	//ステージの更新
	//void update(float delta_time);
	//ステージの描画
	void draw() const;

	//球と地形の当たり判定
	bool collide(const BoundingSphere& sphere, GSvector3* center = nullptr);
	//線分と地形の当たり判定
	bool collide(const Line& line, GSvector3* intersect = nullptr);

private:
	//地形メッシュ
	GSuint mesh_;
	//地形コライダー
	GSuint collider_;
};
#endif//!STAGE_H_

