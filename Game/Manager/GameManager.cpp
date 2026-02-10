#include <iostream>
#include "GameManager.h"
#include "Util/Util.h"
#include "Render/Renderer.h"

using namespace Wanted;

GameManager& GameManager::Get()
{
	static GameManager instance;
	return instance;
}

GameManager::GameManager()
{
	isGameOver = false;
}

GameManager::~GameManager()
{
}