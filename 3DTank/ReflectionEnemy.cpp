#include "ReflectionEnemy.h"
#include "IWorld.h"
#include "CannonBall.h"
#include "Assets.h"

const float MoveSpeed{ 0.2f };    //移動速さ
const float EnemyHeight{ 2.0f };  //境界球中心の高さ
const float ShotInterval{ 90.0f };                 //弾の発射間隔
const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };  //弾を撃つ位置のオフセット
const float CannonRange{ 16.0f };                  //弾が届く距離

ReflectionEnemy::ReflectionEnemy(IWorld* world, const GSvector3& position):
	Enemy{world, position}
{
	name_ = "ReflectionEnemy";
	tag_ = "EnemyTag";
	velocity_ = GSvector3{ 0.0f, 0.0f, MoveSpeed };
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
	mesh_ = Mesh_Enemy;
}

void ReflectionEnemy::shoot(float delta_time)
{
	//一定時間ごとに弾を発射
	shot_timer_ += delta_time;
	if (shot_timer_ >= ShotInterval) {
		//プレイヤーを取得
		Actor* player = world_->find_actor("Player");
		//見つからなかったら終了
		if (!player) return;
		//弾生成位置
		GSvector3 position = transform_.position() + CannonOffset;
		//プレイヤー方向を計算
		GSvector3 direction = player->transform().position() - transform_.position();
		direction.y = 0.0f;
		//射程範囲を制限しながら、弾着弾位置を算出
		GSvector3 destination = transform_.position() + GSvector3::clampMagnitude(direction, CannonRange);
		//弾を生成
		world_->add_actor(new CannonBall{ world_, position, destination, "EnemyCannonBallTag" });
		shot_timer_ -= ShotInterval;
	}
}

void ReflectionEnemy::react_wall()
{
	//移動量反転
	velocity_.z = -velocity_.z;
}
