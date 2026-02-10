#include "SnowRPGLevel.h"
#include "Actor/Player.h"
#include "Core/Input.h"
#include "Actor/Envrionments/En_Wall.h"
#include "Actor/Envrionments/En_Empty.h"
#include "Util/Util.h"
#include "Actor/Enemy/Thief.h"
#include "Actor/Enemy/Fly.h"
#include "Manager/GameManager.h"
#include "Render/Renderer.h"
#include "Actor/Enemy/Spawner.h"
#include "Engine/Engine.h"

#include <iostream>

using namespace Wanted;

SnowRPGLevel::SnowRPGLevel()
{
	Engine::Get().SetNewLevel(this);
	//LoadMap("GameMap.txt");
	LoadMap("TestMap.txt");
	//LoadMap("TestMap_1.txt");
}

SnowRPGLevel::~SnowRPGLevel()
{
}

void SnowRPGLevel::Draw()
{
	super::Draw();

	DrawScore();

	if (GameManager::Get().isGameOver)
		DrawGameOver();
}

void SnowRPGLevel::DrawScore()
{
	static char buffer[64];
	sprintf_s(buffer, sizeof(buffer), "Score : %d", GameManager::Get().GetScore());

	Renderer::Get().Submit(buffer, Vector2(screenSize.x / 4.0f, screenSize.y + 2), Color::White);
}

void SnowRPGLevel::DrawGameClear()
{
	Util::SetConsolePosition(Vector2(30, 0));
	Util::SetConsoleTextColor(Color::White);

	std::cout << "Game Clear!";
}

void SnowRPGLevel::DrawGameOver()
{
	Renderer::Get().Submit("Game Over!", Vector2(screenSize.x / 4.0f, screenSize.y / 2.0f), Color::White);
}


void SnowRPGLevel::LoadMap(const char* filename)
{
	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	if (file == nullptr)
	{
		std::cerr << "Failed to open map file\n";
		
		__debugbreak();
	}

	fseek(file, 0, SEEK_END);

	size_t fileSize = ftell(file);

	rewind(file);

	char* data = new char[fileSize + 1];

	size_t readSize = fread(data, sizeof(char), fileSize, file);
	
	int index = 0;
	
	while (true)
	{
		if (index >= fileSize)
			break;

		char mapCharacter = data[index++];

		if (mapCharacter == '\n')
		{
			++screenSize.y;
			screenSize.x = 0;
			continue;
		}
		
		switch (mapCharacter)
		{
		case '#':
			AddNewActor(new En_Wall(screenSize));
			break;

		case '.':
			AddNewActor(new En_Empty(screenSize));
			break;

		case 'p':
		{
			Player* player = new Player(screenSize);
			GameManager::Get().SetPlayer(player);
			AddNewActor(player);
			break;
		}

		case 't':
			AddNewActor(new Thief(screenSize));
			break;

		case 'f':
			AddNewActor(new Fly(screenSize));
			break;

		case 's':
			Spawner* spawner = new Spawner(screenSize);
			GameManager::Get().AddSpawner(spawner);
			AddNewActor(spawner);
			break;
		}

		++screenSize.x;
	}

	delete[] data;

	fclose(file);
}
