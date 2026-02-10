#include "DeadEffect.h"
#include "Engine/Engine.h"

DeadEffect::DeadEffect(char* image, const Vector2& position)
	: super(image, position, Color::White)
{
	timer.SetTargetTime(2);
}

void DeadEffect::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	timer.Tick(deltaTime);
	if (!timer.IsTimeOut())
		return;

	timer.Reset();
	Destroy();
}
