#include "EnemySpawner.h"
#include "Enemy.h"
#include "Util/Util.h"
#include "Level/Level.h"
#include "Actor/Enemy/Thief.h"

EnemySpawner::EnemySpawner()
{
	spawners = {};
	// 적 생성 타이머 설정.
	timer.SetTargetTime(Util::RandomRange(5.0f, 10.0f));
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	SpawnEnemy(deltaTime);
}

void EnemySpawner::SpawnEnemy(float deltaTime)
{
	timer.Tick(deltaTime);
	if (!timer.IsTimeOut())
		return;

	timer.Reset();

	int spawnIndex = Util::Random(0, spawners.size() - 1);

	int xPosition = Util::Random(-3, 3);
	int yPosition = Util::Random(-2, -1);
	
	Vector2 spawnPos = spawners[spawnIndex]->GetPosition();
	spawnPos.x -= xPosition;
	spawnPos.y -= yPosition;

	GetOwner()->AddNewActor(
		new Thief(spawnPos)
	);
}
