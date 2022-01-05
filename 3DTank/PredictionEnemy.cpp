#include "PredictionEnemy.h"
#include "IWorld.h"
#include "Assets.h"

const float EnemyHeight{ 2.0f };  //境界球中心の高さ
const float MoveSpeed{ 0.1f };    //移動速さ

PredictionEnemy::PredictionEnemy(IWorld* world, const GSvector3& position):
	Enemy{world, position, 90.0f, 30.0f}
{
	name_ = "PredictionEnemy";
	tag_ = "EnemyTag";
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
	mesh_ = Mesh_PredictionEnemy;
}

//プレイヤーから逃げる
void PredictionEnemy::move(float delta_time)
{
	//プレイヤーを検索
	Actor* player = world_->find_actor("Player");
	if (!player) return;

	//プレイヤーから自分へ向かう方向を取得
	GSvector3 direction = transform_.position() - player->transform().position();
	direction.y = 0.0f;
	//最大速度を制限
	direction = GSvector3::clampMagnitude(direction, MoveSpeed);
	//現在速度水平成分を取得
	GSvector3 velocity{ velocity_.x, 0.0f, velocity_.z };
	//目標速度と現在速度を補間
	velocity = GSvector3::slerp(direction, velocity, 0.05f);
	//移動量を反映
	transform_.translate(velocity * delta_time);
}

void PredictionEnemy::shoot(float delta_time)
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
		//発射先（射的距離補正前）
		//TODO:砲丸クラスの定数をどうにか取得する
		GSvector3 destination = player->transform().position() + player->velocity() * 80.0f;
		//発射方向（射的距離補正前）
		GSvector3 direction = destination - transform_.position();
		direction.y = 0.0f;
		//発射方向（射的距離補正後）
		direction = GSvector3::clampMagnitude(direction, CannonRange);
		//発射先（射的距離補正後）
		destination = position + direction;
		//弾を生成
		generate_cannon_ball(position, destination);
		shot_timer_ -= ShotInterval;
	}
}
