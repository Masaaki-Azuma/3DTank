#include "BlastCannonBall.h"
#include "PlayScene/IWorld.h"
#include "PlayScene/Stage.h"
#include "../Blast.h"
#include "Assets.h"

const float Gravity{ -0.01f };
const float CannonVerticalSpeed{ 0.7f };  //’e‚Ì‰”’¼‰‘¬“x
const float CannonVelocityFactor{ -2 * CannonVerticalSpeed / Gravity };  ////’…’e‚Ü‚Å‚É‚©‚©‚éŽžŠÔA’e‚Ì…•½‘¬“x‚ðŒˆ’è‚·‚éŒW”A= -2*CannonVerticalSpeed/CannonBall::Gravity

BlastCannonBall::BlastCannonBall(IWorld* world, const GSvector3& position, const GSvector3& destination):
	CannonBall{world, position, destination}
{
	name_ = "BlastCannonBall";
	tag_ = "EnemyCannonTag";
	mesh_ = Mesh_CannonBall;

	GSvector3 relative_position = destination - position;
	velocity_ = relative_position / CannonVelocityFactor;
	velocity_.y = CannonVerticalSpeed;
}

void BlastCannonBall::react(Actor& other)
{
	//“G’e‚ªŽ©‹@‚É“–‚½‚Á‚½‚çÁ–Å
	if (other.tag() == "PlayerTag") {
		world_->add_actor(new Blast{ transform_.position() });
		die();
	}
}

void BlastCannonBall::move(float delta_time)
{
	//d—Í‚ðì—p
	velocity_.y += Gravity * delta_time;
	//ˆÚ“®—Ê‚ð”½‰f
	transform_.translate(velocity_ * delta_time);
}

void BlastCannonBall::collide_field()
{
	//’nŒ`‚É“–‚½‚Á‚½‚çíœ
	if (world_->stage().collide(collider())) {
		world_->add_actor(new Blast{ transform_.position() });
		die();
	}
}
