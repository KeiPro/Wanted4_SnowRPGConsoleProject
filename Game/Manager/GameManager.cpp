#include <iostream>
#include "GameManager.h"

using namespace Wanted;

GameManager& GameManager::Get()
{
	static GameManager instance;
	return instance;
}

GameManager::GameManager()
{
	
}

GameManager::~GameManager()
{
}
