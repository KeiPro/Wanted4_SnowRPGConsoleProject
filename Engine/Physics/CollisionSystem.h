#pragma once

#include "Common/RTTI.h"

#include <vector>

namespace Wanted
{
	class WANTED_API ICollider
	{
		
	};

	class CollisionSystem : ICollider
	{
	public:
		CollisionSystem();
		~CollisionSystem();

		void BeginPlay();
		void Tick(float deltaTime);

		void Register(ICollider* newCollider);
		void UnRegister(ICollider* colliderToRemove);

	private:

		std::vector<ICollider*> colliders;
	};
}
