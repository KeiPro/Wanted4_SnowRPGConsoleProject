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
	void WarnNextSpawnPos();

private:

	float elapsedTime = 0.0f;
	float baseSpawnTime = 5.0f;
	int initCount = 0;
	float remainTime = 0.0f;

	// 생성 타이머.
	Timer timer;
	std::vector<Spawner*> spawners;
	bool isSelected = false;
	Vector2 spawnPos = {};
};
