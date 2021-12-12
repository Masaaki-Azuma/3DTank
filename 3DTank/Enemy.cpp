#include "Enemy.h"
#include "IWorld.h"
#include "Field.h"
#include "Line.h"
#include "CannonBall.h"
#include "Assets.h"

const float MoveSpeed{ 0.2f };
const float Gravity{ -0.05f };
const float EnemyHeight{ 2.0f };
const float FootOffset{ 0.1f };
const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };
const float CannonSpeed{ 0.2f };

Enemy::Enemy(IWorld* world, const GSvector3& position)
{
	world_ = world;
	name_ = "Enemy";
	tag_ = "EnemyTag";
	transform_.position(position);
	velocity_ = GSvector3{ 0.0f, 0.0f, -MoveSpeed };
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, EnemyHeight, 0.0f} };
}

void Enemy::update(float delta_time)
{
	//移動
	move(delta_time);
	//自由落下
	free_fall(delta_time);
	//弾を発射
	shoot(delta_time);
	//地形と衝突判定
	collide_field();
}

void Enemy::draw() const
{
	//メッシュの描画
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(Mesh_Enemy);
	glPopMatrix();

	//ForDebug
	//境界球の描画
	collider().draw();
}

void Enemy::react(Actor& other)
{
	//自機弾に当たったら死亡
	if (other.tag() == "PlayerCannonBallTag") {
		die();
	}
}

void Enemy::move(float delta_time)
{
	//移動量を反映
	transform_.translate(velocity_, GStransform::Space::World);
}

void Enemy::free_fall(float delta_time)
{
	//重力を作用
	velocity_.y += Gravity * delta_time;
	//上下方向の移動量を反映
	transform_.translate(GSvector3{ 0.0f, velocity_.y * delta_time, 0.0f }, GStransform::Space::World);
}

void Enemy::shoot(float delta_time)
{
	//一定時間ごとに弾を発射
	shot_timer_ += delta_time;
	if (shot_timer_ >= 60.0f) {
		//プレイヤーを取得
		Actor* player = world_->find_actor("Player");
		//見つからなかったら終了
		if (!player) return;
		//プレイヤー方向を計算
		GSvector3 direction = player->transform().position() - transform_.position();
		//y成分は無視
		direction.y = 0.0f;
		//弾の移動量を算出
		GSvector3 velocity = direction.normalized() * CannonSpeed;
		//y成分は一定
		velocity.y = 0.8f;
		//弾を生成
		world_->add_actor(new CannonBall{ world_, transform_.position() + CannonOffset, velocity, "EnemyCannonBallTag"});
		shot_timer_ -= 60.0f;
	}
}

void Enemy::collide_field()
{
	//地形との位置補正
	//地面との衝突判定
	Line line{ collider().center(),  transform_.position() + GSvector3{ 0.0f, -FootOffset, 0.0f } };
	GSvector3 intersect;
	//衝突したら垂直方向に押し戻し
	if (world_->field().collide(line, &intersect)) {
		GSvector3 position = line.start();
		position.y = intersect.y - FootOffset;
		transform_.position(position);
		velocity_.y = 0.0f;
	}
	//壁との衝突判定
	GSvector3 center;
	//衝突したら水平方向に押し戻し
	if (world_->field().collide(collider(), &center)) {
		//yはそのまま
		center.y = transform_.position().y;
		transform_.position(center);
		//移動量反転
		velocity_.z = -velocity_.z;
	}
}
