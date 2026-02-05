#include "CollisionSystem.h"
#include "../Component/Collider/BoxCollider.h"

using namespace Wanted;

CollisionSystem::CollisionSystem()
{

}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::BeginPlay()
{

}

void CollisionSystem::Tick(float deltaTime)
{
	// collision
	int totalSize = colliders.size();
	for (int i = 0; i < totalSize - 1; i++)
	{
		if (colliders[i]->GetIsActive() == false)
			continue;

		for (int j = i + 1; j < totalSize; j++)
		{
			if (colliders[j]->GetIsActive() == false)
				continue;

			if (colliders[i]->AABBCollision(colliders[j]))
			{
				colliders[i]->NotifyCollision(colliders[j]);
				colliders[j]->NotifyCollision(colliders[i]);
			}
		}
	}

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
}

void CollisionSystem::Register(BoxCollider* newCollider)
{
	addRequested.emplace_back(newCollider);
}

void CollisionSystem::UnRegister(BoxCollider* collider)
{
	removeRequested.emplace_back(collider);
}
