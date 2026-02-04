#include <iostream>
#include "Engine/Engine.h"
#include "Level/SokobanLevel.h"
#include "Game/Game.h"

using namespace Wanted;

int main()
{
	Game game;
	game.Run();
	std::cin.get();
}