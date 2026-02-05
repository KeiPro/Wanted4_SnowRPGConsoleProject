#include "CollisionSystem.h"
#include "../Component/Collider/BoxCollider.h"

using namespace Wanted;

CollisionSystem::CollisionSystem()
{

}

CollisionSystem::~CollisionSystem()
{
	for (BoxCollider* collider : colliders)
	{
		if (collider)
		{
			delete collider;
			collider = nullptr;
		}
	}
}

void CollisionSystem::BeginPlay()
{

}

void CollisionSystem::Tick(float deltaTime)
{
	for (BoxCollider* const boxCollider : colliders)
	{
		boxCollider->Tick(deltaTime);
	}
}

void CollisionSystem::ProcessAddAndDestroyColliders()
{
	for (int ix = 0; ix < static_cast<int>(colliders.size()); )
	{
		if (colliders[ix]->DestroyRequested())
		{
			delete colliders[ix];
			colliders.erase(colliders.begin() + ix);
			continue;
		}

		++ix;
	}

	if (addRequestedColliders.size() == 0)
		return;

	for (BoxCollider* const boxCollider : addRequestedColliders)
	{
		colliders.emplace_back(boxCollider);
	}

	addRequestedColliders.clear();
}


void CollisionSystem::Register(BoxCollider* newCollider)
{
	addRequestedColliders.emplace_back(newCollider);
}