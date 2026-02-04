#pragma once

#include "Actor/Actor.h"

using namespace Wanted;

class En_Empty : public Actor
{
	RTTI_DECLARATIONS(En_Empty, Actor)

public:
	
	En_Empty(const Vector2& position);

private:
};

