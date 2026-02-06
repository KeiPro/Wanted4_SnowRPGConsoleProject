#include "Level.h"
#include "Actor/Actor.h"
#include "Physics/CollisionSystem.h"

namespace Wanted
{
	Level::Level()
	{
		collisionSystem = new CollisionSystem();
	}

	Level::~Level()
	{
		for (Actor* actor : actors)
		{
			if (actor)
			{
				delete actor;
				actor = nullptr;
			}
		}

		actors.clear();

		delete collisionSystem;
		collisionSystem = nullptr;
	}

	void Level::BeginPlay()
	{
		for (Actor* actor : actors)
		{
			if (actor->HasBeganPlay())
				continue;

			actor->BeginPlay();
		}
	}

	void Level::Tick(float deltaTime)
	{
		for (Actor* actor : actors)
		{
			actor->Tick(deltaTime);
		}

		collisionSystem->Tick(deltaTime);
	}

	void Level::Draw()
	{
		for (Actor* const actor : actors)
		{
			if (!actor->IsActive())
				continue;

			actor->Draw();
		}
	}

	void Level::AddNewActor(Actor* newActor)
	{
		addRequestedActors.emplace_back(newActor);
		newActor->SetOwner(this);
	}

	void Level::ProcessAddAndDestroyActors()
	{
		for (int ix = 0; ix < static_cast<int>(actors.size()); )
		{
			if (actors[ix]->DestroyRequested())
			{
				delete actors[ix];
				actors.erase(actors.begin() + ix);
				continue;
			}

			++ix;
		}

		if (addRequestedActors.size() == 0)
			return;

		for (Actor* const actor : addRequestedActors)
		{
			actors.emplace_back(actor);
		}

		addRequestedActors.clear();
	}
}