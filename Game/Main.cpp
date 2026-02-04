#include <iostream>
#include "Engine/Engine.h"
#include "Level/SnowRPGLevel.h"
#include "Game/Game.h"

using namespace Wanted;

int main()
{
	Game game;
	game.Run();
	std::cin.get();
}