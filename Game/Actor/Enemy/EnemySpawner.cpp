#include "EnemySpawner.h"
#include "Enemy.h"
#include "Util/Util.h"
#include "Level/Level.h"
#include "Actor/Enemy/Thief.h"
#include "Render/Renderer.h"

EnemySpawner::EnemySpawner()
{
	spawners = {};
	timer.SetTargetTime(baseSpawnTime);
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if (isSelected == false)
	{
		if (spawners.size() == 0)
			return;

		isSelected = true;
		int spawnIndex = Util::Random(0, spawners.size() - 1);
		int xPosition = Util::Random(-3, 3);
		spawnPos = spawners[spawnIndex]->GetPosition();
		spawnPos.x += xPosition;
		return;
	}

	elapsedTime += deltaTime;
	if (elapsedTime >= 10.0f)
	{
		elapsedTime = 0.0f;
		initCount++;
		if (initCount < 4)
			timer.SetTargetTime(baseSpawnTime - initCount * 0.75f);
	}

	Renderer::Get().Submit("!", spawnPos, Color::Warning, 1);

	timer.Tick(deltaTime);
	if (!timer.IsTimeOut())
		return;

	timer.Reset();
	SpawnEnemy(deltaTime);
	isSelected = false;
}


void EnemySpawner::SpawnEnemy(float deltaTime)
{
	

	GetOwner()->AddNewActor(new Thief(spawnPos));
}

void EnemySpawner::WarnNextSpawnPos()
{


}
