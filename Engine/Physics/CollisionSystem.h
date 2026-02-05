#pragma once

#include "Common/RTTI.h"

#include <vector>

namespace Wanted
{
	class BoxCollider;
	class CollisionSystem
	{
	public:
		CollisionSystem();
		~CollisionSystem();

		void BeginPlay();
		void Tick(float deltaTime);

		void Register(BoxCollider* newCollider);
		void UnRegister(BoxCollider* colliderToRemove);

	private:

		std::vector<BoxCollider*> colliders;

		std::vector<BoxCollider*> addRequested;
		std::vector<BoxCollider*> removeRequested;
	};
}
