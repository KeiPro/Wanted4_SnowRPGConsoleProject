#include "CollisionSystem.h"

using namespace Wanted;

CollisionSystem::CollisionSystem()
{

}

CollisionSystem::~CollisionSystem()
{
	for (ICollider* collider : colliders)
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

}

void CollisionSystem::Register(ICollider* newCollider)
{

}

void CollisionSystem::UnRegister(ICollider* colliderToRemove)
{

}