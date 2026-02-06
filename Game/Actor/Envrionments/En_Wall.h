#pragma once
#include "Actor/Actor.h"

using namespace Wanted;

class En_Wall : public Actor
{
	RTTI_DECLARATIONS(En_Wall, Actor)

public:
	En_Wall(const Vector2& position);
};
