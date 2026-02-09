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

void Wanted::CollisionSystem::RemovePairsIncluding(BoxCollider* c)
{
	const std::uintptr_t pc = (std::uintptr_t)c;

	auto removeIfContains = [&](auto& set)
	{
		for (auto it = set.begin(); it != set.end(); )
		{
			if (it->a == pc || it->b == pc) 
				it = set.erase(it);
			else 
				++it;
		}
	};

	removeIfContains(previousPairs);
	removeIfContains(currentPairs);
}

void CollisionSystem::Tick(float deltaTime)
{
	ApplyNewRequested();

	/*for (BoxCollider* c : colliders)
	{
		if (!c || !c->GetIsActive()) continue;
		c->SyncToOwner();
	}*/

	MakePairAndSwapPair();
}

void Wanted::CollisionSystem::MakePairAndSwapPair()
{
	currentPairs.clear();

	const int n = colliders.size();
	for (int i = 0; i < n; i++)
	{
		BoxCollider* a = colliders[i];
		if (!a || a->GetIsActive() == false || a->DestroyRequested())
			continue;

		for (int j = i + 1; j < n; ++j)
		{
			BoxCollider* b = colliders[j];
			if (!b || b->GetIsActive() == false || b->DestroyRequested()) 
				continue;

			if (a->AABBCollision(b))
			{
				currentPairs.insert(MakeKey(a, b));
			}
		}
	}

	// 2) Enter / Stay
	for (const auto& key : currentPairs)
	{
		std::pair<BoxCollider*, BoxCollider*> pair = DecodeKey(key);
		BoxCollider* a = pair.first;
		BoxCollider* b = pair.second;

		if (previousPairs.find(key) == previousPairs.end())
		{
			if (a && b)
			{
				a->NotifyEnter(b);
				b->NotifyEnter(a);
			}
		}
		else
		{
			// Stay
			if (a && b)
			{
				a->NotifyStay(b);
				b->NotifyStay(a);
			}
		}
	}

	// 3) Exit
	for (const auto& key : previousPairs)
	{
		if (currentPairs.find(key) == currentPairs.end())
		{
			std::pair<BoxCollider*, BoxCollider*> pair = DecodeKey(key);
			BoxCollider* a = pair.first;
			BoxCollider* b = pair.second;
			if (a && b)
			{
				a->NotifyExit(b);
				b->NotifyExit(a);
			}
		}
	}

	// 4) 스왑
	previousPairs = currentPairs;
}

void Wanted::CollisionSystem::ApplyNewRequested()
{
	for (int i = 0; i < static_cast<int>(colliders.size()); )
	{
		if (colliders[i]->DestoryRequested())
		{
			delete colliders[i];
			colliders.erase(colliders.begin() + i);
			continue;
		}

		++i;
	}

	if (addRequestedColliders.size() == 0)
		return;

	for (BoxCollider* const collider : addRequestedColliders)
	{
		colliders.emplace_back(collider);
	}

	addRequestedColliders.clear();
}

void CollisionSystem::Register(BoxCollider* newCollider)
{
	if (newCollider != nullptr)
		addRequestedColliders.emplace_back(newCollider);
}