#pragma once
#include "Actor/Actor.h"

namespace Wanted
{
	class Spawner : public Actor
	{
		RTTI_DECLARATIONS(Spawner, Actor)

	public:

		Spawner(const Vector2& position);
		~Spawner();

	};
}

