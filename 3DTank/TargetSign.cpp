#include "TargetSign.h"
#include "IWorld.h"
#include "Stage.h"
#include "Assets.h"

const float MoveSpeed{ 0.5f };     //移動速さ
const float Height{ 0.9f };        //一定高さ、これより下げると地形に埋まる
const float RangeRadius{ 16.0f };  //プレイヤーから離れられる最大距離
const GSrect Size{ -2,-2, 2, 2 };
const GSrect StageSize{ -33,-20.5f, 33, 20.5 };

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
	move(delta_time);
}

void TargetSign::draw() const
{
	//メッシュの描画
	glPushMatrix();
	glMultMatrixf(transform_.localToWorldMatrix());
	gsDrawMesh(Mesh_TargetSign);
	glPopMatrix();
}

void TargetSign::move(float delta_time)
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
	//壁による押し出し前のワールド座標を算出
	GSvector3 position = owner_position + offset_;
	//壁の内側に制限
	collide_wall(position);
	//壁による押し出し後のワールド座標を算出
	position = owner_position + offset_;
	//プレイヤーから相対移動した座標へ移動
	transform_.position(position);
}

void TargetSign::collide_wall(const GSvector3& position)
{
	//ステージ外枠と照準の大きさから求まる、位置の限界値
	static const float left_limit{ StageSize.left - Size.left };
	static const float right_limit{ StageSize.right - Size.right };
	static const float top_limit{ StageSize.top - Size.top };
	static const float bottom_limit{ StageSize.bottom - Size.bottom };
	//壁に埋まった長さぶん、オフセットを押し戻す
	if (position.x < left_limit) {
		offset_.x += left_limit - position.x;
	}
	else if (position.x > right_limit) {
		offset_.x += right_limit - position.x;
	}

	if (position.z < top_limit) {
		offset_.z += top_limit - position.z;
	}
	else if (position.z > bottom_limit) {
		offset_.z += bottom_limit - position.z;
	}
}

//HACK:collide_fieldはActorでまとめるべきでは？(virtualでオーバーライドできるようにしておく)
