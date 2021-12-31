#include "Enemy.h"
#include "IWorld.h"
#include "Stage.h"
#include "Line.h"
//#include "CannonBall.h"
#include "CommonCannonBall.h"
#include "Assets.h"

const float Gravity{ -0.02f };                     //重力加速度
//const float EnemyHeight{ 2.0f };                   //境界球中心の高さ
const float FootOffset{ 0.1f };                    //地面との当たり判定用の足元オフセット
//const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };  //弾を撃つ位置のオフセット

Enemy::Enemy(IWorld* world, const GSvector3& position, float shot_inteval, float cannon_range):
	mesh_{Mesh_Enemy},
	ShotInterval{shot_inteval},
	CannonRange{cannon_range}
{
	world_ = world;
	name_ = "Enemy";
	tag_ = "EnemyTag";
	transform_.position(position);
}

void Enemy::update(float delta_time)
{
	//移動
	move(delta_time);
	//自由落下
	free_fall(delta_time);
	//地形と衝突判定
	collide_field();
	//弾を発射
	shoot(delta_time);
}

void Enemy::draw() const
{
	//メッシュの描画
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(mesh_);
	glPopMatrix();

	//ForDebug
	//境界球の描画
	collider().draw();
	BoundingSphere{ CannonRange, transform_.position()}.draw();
}

void Enemy::react(Actor& other)
{
	//自機弾に当たったら死亡
	if (other.tag() == "PlayerCannonBallTag") {
		die();
	}
	else if(other.tag() == "PlayerTag" || other.tag() == "EnemyTag"){
		collide_actor(other);
	}

}

void Enemy::move(float delta_time)
{
	//移動量を反映
	transform_.translate(velocity_, GStransform::Space::World);
}

//着弾位置を算出し、砲丸クラスに渡して生成
void Enemy::shoot(float delta_time)
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
		generate_cannon_ball(position, destination);
		shot_timer_ -= ShotInterval;
	}
}

void Enemy::generate_cannon_ball(const GSvector3& position, const GSvector3& destination)
{
	world_->add_actor(new CommonCannonBall{ world_, position, destination });
}

void Enemy::react_wall()
{
}

/*以下は書き換えない*/
void Enemy::free_fall(float delta_time)
{
	//重力を作用
	velocity_.y += Gravity * delta_time;
	//上下方向の移動量を反映
	transform_.translate(GSvector3{ 0.0f, velocity_.y * delta_time, 0.0f }, GStransform::Space::World);
}

void Enemy::collide_field()
{
	//地形との位置補正
	//地面との衝突判定
	Line line{ collider().center(),  transform_.position() + GSvector3{ 0.0f, -FootOffset, 0.0f } };
	GSvector3 intersect;
	//衝突したら垂直方向に押し戻し
	if (world_->stage().collide(line, &intersect)) {
		GSvector3 position = line.start();
		position.y = intersect.y - FootOffset;
		transform_.position(position);
		velocity_.y = 0.0f;
	}
	//壁との衝突判定
	GSvector3 center;
	//衝突したら水平方向に押し戻し
	if (world_->stage().collide(collider(), &center)) {
		//yはそのまま
		center.y = transform_.position().y;
		transform_.position(center);
		react_wall();
	}
}

void Enemy::collide_actor(Actor& other)
{
	//相手から自分へ向かうベクトル
	GSvector3 direction = transform_.position() - other.transform().position();
	direction.y = 0.0f;
	//取るべき距離
	float length = collider().radius() + other.collider().radius();
	//重なり長さ
	float overlap = length - direction.length();
	//押し出し後の位置
	GSvector3 velocity = direction.normalized() * overlap;
	//計算値分移動
	transform_.translate(velocity, GStransform::Space::World);
	//地形からはみ出ないように再判定
	collide_field();
}
