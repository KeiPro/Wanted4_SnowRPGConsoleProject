#pragma once

#include "Common/RTTI.h"

#include <vector>

namespace Wanted
{
	class BoxCollider;
	class WANTED_API CollisionSystem
	{
		
	public:
		CollisionSystem();
		~CollisionSystem();

		void Tick(float deltaTime);

		void Register(BoxCollider* newCollider);
		void UnRegister(BoxCollider* colliderToRemove);

		static CollisionSystem& Get();

	private:

		std::vector<BoxCollider*> colliders;

		std::vector<BoxCollider*> addRequested;
		std::vector<BoxCollider*> removeRequested;

		static CollisionSystem* instance;
	};
}
