#include <iostream>
#include "GameManager.h"
#include "Util/Util.h"
#include "Render/Renderer.h"
#include "Actor/Enemy/EnemySpawner.h"
#include "Actor/ItemSpawner.h"
#include "Engine/Engine.h"
#include "Level/Level.h"

using namespace Wanted;


GameManager& GameManager::Get()
{
	static GameManager instance;
	return instance;
}

GameManager::GameManager()
{
	enemySpawner = new EnemySpawner();
	Engine::Get().GetLevel()->AddNewActor(enemySpawner);

	itemSpawner = new ItemSpawner();
	Engine::Get().GetLevel()->AddNewActor(itemSpawner);
	isGameOver = false;
}

GameManager::~GameManager()
{
}

void GameManager::AddSpawner(Spawner* spawner)
{
	if (spawner != nullptr)
		enemySpawner->AddSpawner(spawner);
}

void GameManager::AddItemSpawner(Spawner* spawner)
{
	if (spawner != nullptr)
		itemSpawner->AddSpawner(spawner);
}

