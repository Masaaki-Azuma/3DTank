#include "PredictionEnemy.h"
#include "PlayScene/IWorld.h"
#include "Assets.h"

enum
{
	Walk,
	Run,
};

const float EnemyHeight{ 2.0f };  //境界球中心の高さ
const float MoveSpeed{ 0.1f };    //移動速さ
const float MaxRunTimer{ 180.0f }; //追跡時間
const float MaxWalkTimer{ 300.0f }; //逃亡時間


PredictionEnemy::PredictionEnemy(IWorld* world, const GSvector3& position):
	Enemy{world, position, 90.0f, 30.0f},
	move_timer_{MaxWalkTimer},
	move_state_{Walk}
{
	name_ = "PredictionEnemy";
	tag_ = "EnemyTag";
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
	mesh_ = Mesh_PredictionEnemy;
}

//プレイヤーから逃げる
void PredictionEnemy::move(float delta_time)
{
	//タイマー更新
	update_timer(delta_time);
	//逃亡タイマーが残っているなら、逃亡状態を続ける
	switch (move_state_) {
	case Walk: move_walk(delta_time); break;
	case Run: move_run(delta_time); break;
	}
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

void PredictionEnemy::move_walk(float delta_time)
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
	//メンバに水平方向移動量をキープ
	velocity_.x = velocity.x;
	velocity_.z = velocity.z;
}

void PredictionEnemy::move_run(float delta_time)
{
	//プレイヤーを検索
	Actor* player = world_->find_actor("Player");
	if (!player) return;

	//プレイヤー方向を取得
	GSvector3 direction = player->transform().position() - transform_.position();
	direction.y = 0.0f;
	//最大速度を制限
	direction = GSvector3::clampMagnitude(direction, MoveSpeed * 1.2f);
	//現在速度水平成分を取得
	GSvector3 velocity{ velocity_.x, 0.0f, velocity_.z };
	//目標速度と現在速度を補間
	velocity = GSvector3::slerp(direction, velocity, 0.05f);
	//移動量を反映
	transform_.translate(velocity * delta_time);
	//メンバに水平方向移動量をキープ
	velocity_.x = velocity.x;
	velocity_.z = velocity.z;
}

void PredictionEnemy::update_timer(float delta_time)
{
	move_timer_ -= delta_time;
	//タイマーの残り時間がなくなったら移動状態変更
	if (move_timer_ <= 0.0f) {
		if (move_state_ == Walk) {
			move_state_ = Run;
			move_timer_ = MaxRunTimer;
		}
		else if (move_state_ == Run) {
			move_state_ = Walk;
			move_timer_ = MaxWalkTimer;
		}
	}
}
