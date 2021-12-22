#include "CommonCannonBall.h"
#include "Assets.h"

const float Gravity{ -0.02f };
const float CannonVerticalSpeed{ 0.8f };  //’e‚Ì‰”’¼‰‘¬“x
const float CannonVelocityFactor{ -2 * CannonVerticalSpeed / Gravity };  ////’…’e‚Ü‚Å‚É‚©‚©‚éŠÔA’e‚Ì…•½‘¬“x‚ğŒˆ’è‚·‚éŒW”A= -2*CannonVerticalSpeed/CannonBall::Gravity

CommonCannonBall::CommonCannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination):
	CannonBall{world, position, destination}
{
	name_ = "CommonCannonBall";
	tag_ = "EnemyCannonBallTag";
	mesh_ = Mesh_CannonBall;

	GSvector3 relative_position = destination - position;
	velocity_ = relative_position / CannonVelocityFactor;
	velocity_.y = CannonVerticalSpeed;
}

void CommonCannonBall::react(Actor& other)
{
	//“G’e‚ª©‹@‚É“–‚½‚Á‚½‚çÁ–Å
	if (other.tag() == "PlayerTag") {
		die();
	}
}

void CommonCannonBall::move(float delta_time)
{
	//d—Í‚ğì—p
	velocity_.y += Gravity * delta_time;
	//ˆÚ“®—Ê‚ğ”½‰f
	transform_.translate(velocity_ * delta_time);
}
