#include "Player.h"
#include "CannonBall.h"
#include "PlayerCannonBall.h"
#include "TargetSign.h"
#include "IWorld.h"
#include "Line.h"
#include "Stage.h"
#include "Assets.h"

const float MoveSpeed{ 0.2f };
const float Gravity{ -0.02f };
const float PlayerHeight{ 2.0f };
const float FootOffset{ 0.1f };
const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };
const float CannonVerticalSpeed{ 0.8f };  //弾の鉛直初速度
const float CannonVelocityFactor{ -2 * CannonVerticalSpeed / Gravity };  //弾の水平速度を決定する係数、= -2*CannonVerticalSpeed/CannonBall::Gravity


Player::Player(IWorld* world, const GSvector3& position)
{
	world_ = world;
	name_ = "Player";
	tag_ = "PlayerTag";
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, PlayerHeight, 0.0f} };
	transform_.position(position);
	world_->add_actor(new TargetSign{ world_, position, *this });
}

void Player::update(float delta_time)
{
	//クリア状態なら移動を操作を禁止
	if (world_->is_level_clear()) return;
	//移動
	move(delta_time);
	//重力による自由落下
	free_fall(delta_time);
	//地形と衝突判定
	collide_field();
	//砲丸の発射
	shoot();
}

void Player::draw() const
{
	//メッシュの描画
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(Mesh_Player);
	glPopMatrix();

	//ForDebug
	//境界球の描画
	collider().draw();
}

void Player::react(Actor& other)
{
	//クリア状態なら死亡しない
	if (world_->is_level_clear()) return;

	//敵弾に当たったら死亡
	if (other.tag() == "EnemyCannonBallTag") {
		die();
	}
	if (other.tag() == "EnemyTag") {
		//押し出し判定
		collide_actor(other);
	}
}

void Player::move(float delta_time)
{
	//移動方向
	GSvector3 direction{ 0.0f, 0.0f, 0.0f };
	//WASD操作で移動
	if (gsGetKeyState(GKEY_D)) {
		direction.x += 1.0f;
	}
	if (gsGetKeyState(GKEY_A)) {
		direction.x -= 1.0f;
	}
	if (gsGetKeyState(GKEY_W)) {
		direction.z -= 1.0f;
	}
	if (gsGetKeyState(GKEY_S)) {
		direction.z += 1.0f;
	}
	//移動量の算出
	GSvector3 velocity = direction.normalized() * MoveSpeed;
	//x,z軸方向の移動量を保存
	velocity_.x = velocity.x;
	velocity_.z = velocity.z;
	//水平方向の移動量を反映
	transform_.translate(velocity * delta_time, GStransform::Space::World);
}

void Player::free_fall(float delta_time)
{
	//重力を作用
	velocity_.y += Gravity * delta_time;
	//上下方向の移動量を反映
	transform_.translate(GSvector3{ 0.0f, velocity_.y * delta_time, 0.0f }, GStransform::Space::World);
}

//着弾位置を砲丸クラスに渡して生成
void Player::shoot()
{
	if (gsGetKeyTrigger(GKEY_SPACE)) {
		Actor* target = world_->find_actor("TargetSign");
		if (!target) return;
		//弾着弾位置
		GSvector3 destination = target->transform().position();
		//弾生成位置
		GSvector3 position = transform_.position() + CannonOffset;
		//弾を生成
		world_->add_actor(new PlayerCannonBall{
			world_, position, destination});
	}
}

void Player::collide_field()
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
		center.y = transform_.position().y;
		transform_.position(center);
	}
}

void Player::collide_actor(Actor& other)
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
