#include "SnowRPGLevel.h"
#include "Actor/Player.h"
#include "Core/Input.h"
#include "Actor/Envrionments/En_Wall.h"
#include "Actor/Envrionments/En_Empty.h"
#include "Util/Util.h"
#include "Actor/Enemy/Thief.h"
#include "Actor/Enemy/Fly.h"
#include "Manager/GameManager.h"

#include <iostream>

using namespace Wanted;

SnowRPGLevel::SnowRPGLevel()
{
	LoadMap("TestMap.txt");
}

SnowRPGLevel::~SnowRPGLevel()
{
}

void SnowRPGLevel::Draw()
{
	super::Draw();

	if (isGameClear)
	{
		Util::SetConsolePosition(Vector2(30, 0));
		Util::SetConsoleTextColor(Color::White);

		std::cout << "Game Clear!";
	}
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
	
	Wanted::Vector2 position;
	
	while (true)
	{
		if (index >= fileSize)
			break;

		char mapCharacter = data[index++];

		if (mapCharacter == '\n')
		{
			++position.y;
			position.x = 0;
			continue;
		}
		
		switch (mapCharacter)
		{
		case '#':
			AddNewActor(new En_Wall(position));
			break;

		case '.':
			AddNewActor(new En_Empty(position));
			break;

		case 'p':
		{
			Player* player = new Player(position);
			GameManager::Get().SetPlayer(player);
			AddNewActor(player);
			break;
		}

		case 't':
			AddNewActor(new Thief(position));
			break;

		case 'f':
			AddNewActor(new Fly(position));
			break;

		}

		++position.x;
	}

	delete[] data;

	fclose(file);
}

bool SnowRPGLevel::CheckGameClear()
{
	return false;
}