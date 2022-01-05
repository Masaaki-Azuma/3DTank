#include "ChaseEnemy.h"
#include "IWorld.h"
#include "Assets.h"

const float EnemyHeight{ 2.0f };  //境界球中心の高さ
const float MoveSpeed{ 0.1f };    //移動速さ


ChaseEnemy::ChaseEnemy(IWorld* world, const GSvector3& position):
	Enemy{world, position}
{
	name_ = "ChaseEnemy";
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
	mesh_ = Mesh_ChaseEnemy;

	velocity_ = GSvector3{ 0.0f, 0.0f, 0.0f };
}

void ChaseEnemy::move(float delta_time)
{
	//プレイヤーを検索
	Actor* player = world_->find_actor("Player");
	if (!player) return;

	//プレイヤー方向を取得
	GSvector3 direction = player->transform().position() - transform_.position();
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
