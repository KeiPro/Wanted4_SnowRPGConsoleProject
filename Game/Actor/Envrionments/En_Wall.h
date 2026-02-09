#pragma once
#include "Actor/Actor.h"

namespace Wanted
{
	class BoxCollider;
	class En_Wall : public Actor
	{
		RTTI_DECLARATIONS(En_Wall, Actor)

	public:
		En_Wall(const Vector2& position);

		BoxCollider* boxCollider = nullptr;
	};
}
