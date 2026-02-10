#pragma once

#include "Actor/Actor.h"
#include "Util/Timer.h"
#include "Actor/Enemy/Spawner.h"

#include <vector>

using namespace Wanted;

class Spanwer;
class EnemySpawner : public Actor
{
	RTTI_DECLARATIONS(EnemySpawner, Actor)

public:
	EnemySpawner();
	~EnemySpawner();

	inline void AddSpawner(Spawner* spawner) { spawners.emplace_back(spawner); }

private:
	virtual void Tick(float deltaTime) override;

	void SpawnEnemy(float deltaTime);

private:
	// 생성 타이머.
	Timer timer;
	std::vector<Spawner*> spawners;
};
