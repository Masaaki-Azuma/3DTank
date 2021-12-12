#include "Player.h"
#include "CannonBall.h"
#include "IWorld.h"
#include "Line.h"
#include "Field.h"
#include "Assets.h"

const float MoveSpeed{ 0.2f };
const float Gravity{ -0.05f };
const float PlayerHeight{ 2.0f };
const float FootOffset{ 0.1f };
const GSvector3 CannonOffset{ 0.0f, 2.5f, 0.0f };

Player::Player(IWorld* world, const GSvector3& position)
{
	world_ = world;
	name_ = "Player";
	tag_ = "PlayerTag";
	collider_ = BoundingSphere{ 1.9f, GSvector3{0.0f, 2.0f, 0.0f} };
	transform_.position(position);
}

void Player::update(float delta_time)
{
	//移動
	move(delta_time);
	//重力による自由落下
	free_fall(delta_time);
	//砲丸の発射
	shoot();
	//地形と衝突判定
	collide_field();
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
	GSvector3 velocity = direction.normalized() * MoveSpeed * delta_time;
	//x,z軸方向の移動量を保存
	velocity_.x = velocity.x;
	velocity_.z = velocity.z;
	//水平方向の移動量を反映
	transform_.translate(velocity, GStransform::Space::World);
}

void Player::free_fall(float delta_time)
{
	//重力を作用
	velocity_.y += Gravity * delta_time;
	//上下方向の移動量を反映
	transform_.translate(GSvector3{ 0.0f, velocity_.y, 0.0f }, GStransform::Space::World);
}

void Player::shoot()
{
	//弾を発射
	if (gsGetKeyTrigger(GKEY_SPACE)) {
		//弾の方向
		GSvector3 direction{ 0.0f, 0.0f, 0.0f };
		if (gsGetKeyState(GKEY_RIGHT)) {
			direction.x += 1.0f;
		}
		if (gsGetKeyState(GKEY_LEFT)) {
			direction.x -= 1.0f;
		}
		if (gsGetKeyState(GKEY_UP)) {
			direction.z -= 1.0f;
		}
		if (gsGetKeyState(GKEY_DOWN)) {
			direction.z += 1.0f;
		}
		//弾の速度
		GSvector3 velocity = direction.normalized() * 0.2;
		//上下方向の移動量は固定
		velocity.y = 0.8f;
		//砲丸を発射
		world_->add_actor(new CannonBall{ world_, transform_.position() + CannonOffset, velocity, "PlayerCannonBallTag" });
	}
}

void Player::collide_field()
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
	//押し出し後の位置
	GSvector3 position = other.transform().position() + direction.normalized() * length;
	//計算値分移動
	transform_.position(position);
}
