#include "SnowRPGLevel.h"
#include "Actor/Player.h"
#include "Core/Input.h"
#include "Actor/Envrionments/En_Wall.h"
#include "Actor/Envrionments/En_Empty.h"
#include "Util/Util.h"

#include <iostream>

/*
# : ��(Wall)
. : �ٴ�(Ground)
p : �÷��̾�
b : �ڽ�
t : Ÿ��.
*/

SnowRPGLevel::SnowRPGLevel()
{
	LoadMap("TestMap.txt");
}

void SnowRPGLevel::Draw()
{
	super::Draw();

	// ���� Ŭ������ ���. �޽��� ���.
	if (isGameClear)
	{
		// �ܼ� ��ġ / ���� ����.
		Util::SetConsolePosition(Vector2(30, 0));
		Util::SetConsoleTextColor(Color::White);

		// ���� Ŭ���� �޽��� ���.
		std::cout << "Game Clear!";
	}
}

void SnowRPGLevel::LoadMap(const char* filename)
{
	// ���� �ε�.
	// ���� ���� ��� �����. ("../Assets/filename")
	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	// ���� ����.
	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	// ����ó��.
	if (file == nullptr)
	{
		// ǥ�� ���� �ܼ� Ȱ��.
		std::cerr << "Failed to open map file\n";
		
		// ����� ��忡�� �ߴ������� �ߴ����ִ� ���.
		__debugbreak();
	}

	// �� �б�.
	// �� ũ�� �ľ� : file position �����͸� ������ ������ �̵�(������ ũ�⸦ �����ϱ� ���ؼ�)
	fseek(file, 0, SEEK_END);

	// �� ��ġ �б�.
	size_t fileSize = ftell(file);

	// File Position ó������ �ǵ�����.
	rewind(file);

	// ���Ͽ��� �����͸� �о�� ���� ����.
	char* data = new char[fileSize + 1];

	// ������ �б�.
	size_t readSize = fread(data, sizeof(char), fileSize, file);
	
	// �о�� ���ڿ��� �м�(�Ľ�)�ؼ� ���.
	// �ε����� ����� �ѹ��ھ� �б�.
	int index = 0;
	
	// ��ü�� ������ ��ġ ��.
	Wanted::Vector2 position;
	//12 22 
	while (true)
	{
		if (index >= fileSize)
			break;

		char mapCharacter = data[index++];

		if (mapCharacter == '\n')
		{
			//std::cout << "\n";
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
			AddNewActor(new Player(position));
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
