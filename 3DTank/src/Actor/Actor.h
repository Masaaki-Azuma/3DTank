#ifndef ACTOR_H_
#define ACTOR_H_

#include <gslib.h>
#include <GStransform.h>
#include <string>
#include "Figure/BoundingSphere.h"

class IWorld;

class Actor
{
public:
	Actor() = default;
	virtual ~Actor() = default;
	//更新
	virtual void update(float delta_time);
	//描画
	virtual void draw() const;
	//GUI描画
	virtual void draw_gui() const;
	//衝突リアクション
	virtual void react(Actor& other);

	//死亡する
	void die();
    //死亡しているか？
	bool is_dead() const;
	//衝突判定
	void collide(Actor& other);

	//衝突しているか？
	bool is_collide(const Actor& other) const;

	//名前を取得
	const std::string& name() const;
	//タグ名を取得
	const std::string& tag() const;
	//位置情報を取得
	const GStransform& transform() const;
	//速度を取得
	const GSvector3& velocity() const;
	//衝突判定図形を取得
	BoundingSphere collider() const;

protected:
	//ワールド
	IWorld* world_{ nullptr };
	//名前
	std::string name_;
	//タグ名
	std::string tag_;
	//位置、回転、拡縮情報
	GStransform transform_;
	//移動量
	GSvector3 velocity_;
	//衝突判定が有効か？
	bool enable_collider_{ true };
	//境界球
	BoundingSphere collider_;
	//死亡フラグ
	bool is_dead_{ false };
};
#endif//!ACTOR_H_

