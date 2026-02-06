#include "CollisionSystem.h"
#include "../Component/Collider/BoxCollider.h"
#include <iostream>

using namespace Wanted;

CollisionSystem* CollisionSystem::instance = nullptr;

CollisionSystem::CollisionSystem()
{
	instance = this;
}

CollisionSystem::~CollisionSystem()
{

}

CollisionSystem& CollisionSystem::Get()
{
	if (!instance)
	{
		std::cout << "Error: CollisionSystem::Get(). instance is null\n";
		__debugbreak();
	}

	return *instance;
}

void CollisionSystem::Tick(float deltaTime)
{
	if (removeRequested.size() != 0)
	{
		for (BoxCollider* const boxCollider : removeRequested)
		{
			auto it = std::find(colliders.begin(), colliders.end(), boxCollider);
			if (it != colliders.end())
			{
				*it = colliders.back();
				colliders.pop_back();
			}
		}
	}

	if (addRequested.size() != 0)
	{
		for (BoxCollider* const boxCollider : addRequested)
		{
			colliders.emplace_back(boxCollider);
		}

		addRequested.clear();
	}

	// collision
	int totalSize = colliders.size();
	for (int i = 0; i < totalSize - 1; i++)
	{
		if (colliders[i]->HasBeganPlay() == false ||
			colliders[i]->GetIsActive() == false)
			continue;

		for (int j = i + 1; j < totalSize; j++)
		{
			if (colliders[j]->HasBeganPlay() == false ||
				colliders[j]->GetIsActive() == false)
				continue;

			if (colliders[i]->AABBCollision(colliders[j]))
			{
				colliders[i]->NotifyCollision(colliders[j]);
				colliders[j]->NotifyCollision(colliders[i]);
			}
		}
	}
}

void CollisionSystem::Register(BoxCollider* newCollider)
{
	addRequested.emplace_back(newCollider);
}

void CollisionSystem::UnRegister(BoxCollider* collider)
{
	removeRequested.emplace_back(collider);
}
