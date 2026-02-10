#pragma once

#include "Actor/Actor.h"
#include "Util/Timer.h"
#include "Actor/Enemy/Spawner.h"

#include <vector>


namespace Wanted
{
	class Spanwer;
	class ItemSpawner : public Actor
	{
		RTTI_DECLARATIONS(ItemSpawner, Actor)

	public:

		ItemSpawner();
		~ItemSpawner();

		inline void AddSpawner(Spawner* spawner) { spawners.emplace_back(spawner); }

	private:
		virtual void Tick(float deltaTime) override;

		void SpawnItem(float deltaTime);

	private:

		float elapsedTime = 0.0f;
		float baseSpawnTime = 7.0f;
		int initCount = 0;
		float remainTime = 0.0f;

		Timer timer;
		std::vector<Spawner*> spawners;
		bool isSelected = false;
		Vector2 spawnPos = {};
	};
}
