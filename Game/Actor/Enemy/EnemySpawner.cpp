#include "EnemySpawner.h"
#include "Enemy.h"
#include "Util/Util.h"
#include "Level/Level.h"
#include "Actor/Enemy/Thief.h"
#include "Render/Renderer.h"

EnemySpawner::EnemySpawner()
{
	spawners = {};
	// 적 생성 타이머 설정.
	timer.SetTargetTime(Util::RandomRange(3.0f, 5.0f));
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if (isSelected == false)
	{
		isSelected = true;
		int spawnIndex = Util::Random(0, spawners.size() - 1);
		int xPosition = Util::Random(-3, 3);
		spawnPos = spawners[spawnIndex]->GetPosition();
		spawnPos.x -= xPosition;
		return;
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
