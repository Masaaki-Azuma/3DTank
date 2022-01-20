#include "Blast.h"
#include <GSeffect.h>
#include "Assets.h"

const float AnimationDuration{ 60.0f };
Blast::Blast(const GSvector3& position)
{
	name_ = "Blast";
	tag_ = "EffectTag";
	effect_handle_ =  gsPlayEffect(Effect_Smoke, &position);
	//transform_.position(position);
}

Blast::~Blast()
{
	gsStopEffect(effect_handle_);
}

void Blast::update(float delta_time)
{
	timer_ += delta_time;
	if (timer_ >= AnimationDuration) {
		die();
	}
}

