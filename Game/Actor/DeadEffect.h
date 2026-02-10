#pragma once

#include "Actor/Actor.h"
#include "Util/Util.h"
#include "Util/Timer.h"

using namespace Wanted;

class DeadEffect : public Actor
{
	RTTI_DECLARATIONS(DeadEffect, Actor)

public:
	DeadEffect(char* str, const Vector2& position);

	virtual void Tick(float deltaTime) override;

	Timer timer;
};
