#include "TargetSign.h"
#include "IWorld.h"
#include "Assets.h"

const float MoveSpeed{ 0.5f };     //移動速さ
const float Height{ 0.9f };        //一定高さ、これより下げると地形に埋まる
const float RangeRadius{ 16.0f };  //プレイヤーから離れられる最大距離

TargetSign::TargetSign(IWorld* world, const GSvector3& position, const Actor& owner):
	offset_{GSvector3::zero()},
	owner_{owner}
{
	world_ = world;
	name_ = "TargetSign";
	tag_ = "TargetSignTag";
	//y座標一定
	transform_.position(GSvector3{ position.x, Height, position.z });
}

void TargetSign::update(float delta_time)
{
	GSvector3 owner_position = owner_.transform().position();
	owner_position.y = Height;
	//移動方向を算出
	GSvector3 direction{ 0.0f, 0.0f, 0.0f };
	if (gsGetKeyState(GKEY_UP)) {
		direction.z -= 1.0f;
	}
	if (gsGetKeyState(GKEY_DOWN)) {
		direction.z += 1.0f;
	}
	if (gsGetKeyState(GKEY_RIGHT)) {
		direction.x += 1.0f;
	}
	if (gsGetKeyState(GKEY_LEFT)) {
		direction.x -= 1.0f;
	}
	//移動量を算出
	GSvector3 velocity = direction.normalized() * MoveSpeed * delta_time;
	//上下方向には動かさない
	velocity.y = 0.0f;
	//移動量分相対座標を変化
	offset_ += velocity;
	//プレイヤーからの相対距離を制限
	offset_ = GSvector3::clampMagnitude(offset_, RangeRadius);
	//プレイヤーから相対移動した座標へ移動
	transform_.position(owner_position + offset_);
}

void TargetSign::draw() const
{
	//メッシュの描画
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(Mesh_TargetSign);
	glPopMatrix();
}
