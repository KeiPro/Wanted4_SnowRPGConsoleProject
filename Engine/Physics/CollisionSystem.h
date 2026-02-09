#pragma once

#include "Common/RTTI.h"

#include <vector>
#include <unordered_set>

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
		void Unregister(BoxCollider* dead);
		void ApplyNewRequested();
		void MakePairAndSwapPair();

		static CollisionSystem& Get();

	private:
		struct PairKey
		{
			std::uintptr_t a;
			std::uintptr_t b;

			bool operator==(const PairKey& other) const 
			{ 
				return a == other.a && b == other.b; 
			}
		};

		struct PairKeyHasher
		{
			size_t operator()(const PairKey& k) const noexcept
			{
				size_t h1 = std::hash<std::uintptr_t>{}(k.a);
				size_t h2 = std::hash<std::uintptr_t>{}(k.b);
				return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
			}
		};

		static PairKey MakeKey(BoxCollider* a, BoxCollider* b)
		{
			std::uintptr_t pa = (std::uintptr_t)a;
			std::uintptr_t pb = (std::uintptr_t)b;
			if (pa < pb) return { pa, pb };
			return { pb, pa };
		}

		static std::pair<BoxCollider*, BoxCollider*> DecodeKey(const PairKey& k)
		{
			return { (BoxCollider*)k.a, (BoxCollider*)k.b };
		}

		void RemovePairsIncluding(BoxCollider* c);

	private:

		std::vector<BoxCollider*> colliders;

		std::unordered_set<PairKey, PairKeyHasher> previousPairs;
		std::unordered_set<PairKey, PairKeyHasher> currentPairs;

		std::vector<BoxCollider*> addRequestedColliders;

		static CollisionSystem* instance;
	};
}
