#pragma once

#include "Common/RTTI.h"

#include <vector>

namespace Wanted
{
	class Actor;
	class Player;
	class Enemy;
	class CollisionSystem;
	class WANTED_API Level : public RTTI
	{
		RTTI_DECLARATIONS(Level, RTTI)

	public:
		Level();
		virtual ~Level();

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		void AddNewActor(Actor* newActor);
		void ProcessAddAndDestroyActors();
		
	protected:
		std::vector<Actor*> actors;
		std::vector<Actor*> addRequestedActors;
		
	private:

		std::vector<Enemy*> enemies;
	};
}
