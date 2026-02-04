#include "SokobanLevel.h"
#include "Actor/Player.h"
#include "Core/Input.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"
#include "Util/Util.h"

#include <iostream>

/*
# : 벽(Wall)
. : 바닥(Ground)
p : 플레이어
b : 박스
t : 타겟.
*/

SokobanLevel::SokobanLevel()
{
	/*if (Wanted::Input::Get().GetKeyDown('Q'))
	{
		
	}*/

	// new TestActor() : r-value reference.
	// AddNewActor(new Player());

	//LoadMap("Stage1.txt");
	LoadMap("Map.txt");
}

void SokobanLevel::Draw()
{
	super::Draw();

	// 게임 클리어인 경우. 메시지 출력.
	if (isGameClear)
	{
		// 콘솔 위치 / 색상 설정.
		Util::SetConsolePosition(Vector2(30, 0));
		Util::SetConsoleTextColor(Color::White);

		// 게임 클리어 메시지 출력.
		std::cout << "Game Clear!";
	}
}

void SokobanLevel::LoadMap(const char* filename)
{
	// 파일 로드.
	// 최종 파일 경로 만들기. ("../Assets/filename")
	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	// 파일 열기.
	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	// 예외처리.
	if (file == nullptr)
	{
		// 표준 오류 콘솔 활용.
		std::cerr << "Failed to open map file\n";
		
		// 디버그 모드에서 중단점으로 중단해주는 기술.
		__debugbreak();
	}

	// 맵 읽기.
	// 맵 크기 파악 : file position 포인터를 파일의 끝으로 이동(파일의 크기를 가늠하기 위해서)
	fseek(file, 0, SEEK_END);

	// 이 위치 읽기.
	size_t fileSize = ftell(file);

	// File Position 처음으로 되돌리기.
	rewind(file);

	// 파일에서 데이터를 읽어올 버퍼 생성.
	char* data = new char[fileSize + 1];

	// 데이터 읽기.
	size_t readSize = fread(data, sizeof(char), fileSize, file);
	
	// 읽어온 문자열을 분석(파싱)해서 출력.
	// 인덱스를 사용해 한문자씩 읽기.
	int index = 0;
	
	// 객체를 생성할 위치 값.
	Wanted::Vector2 position;

	while (true)
	{
		if (index >= fileSize)
			break;

		// 캐릭터 읽기.
		char mapCharacter = data[index++];

		// 개행 문자 처리.
		// text모드로 읽으면 개행문자를 처리해준다?
		if (mapCharacter == '\n')
		{
			//std::cout << "\n";
			++position.y;
			position.x = 0;
			continue;
		}
		
		// 한 문자씩 처리.
		switch (mapCharacter)
		{
		case '#':
		case '1':
			//std::cout << "#";
			AddNewActor(new Wall(position));
			break;

		case '.':
			//std::cout << " ";
			AddNewActor(new Ground(position));
			break;

		case 'p':
			//std::cout << "P";
			AddNewActor(new Player(position));
			AddNewActor(new Ground(position));
			break;

		case 'b':
			//std::cout << "B";
			AddNewActor(new Box(position));
			AddNewActor(new Ground(position));
			break;

		case 't':
			AddNewActor(new Target(position));
			++targetScore;
			//std::cout << "T";
			break;
		}

		++position.x;
	}

	// 사용한 버퍼 해제.
	delete[] data;

	// 파일이 정상적으로 열렸으면 닫기.
	fclose(file);
}

bool SokobanLevel::CanMove(const Wanted::Vector2& playerPosition, const Wanted::Vector2& nextPosition)
{
	// 레벨에 있는 박스 액터 모으기.
	// 박스는 플레이어가 밀기 등 추가적으로 처리해야 하기 때문에.
	std::vector<Actor*> boxes;
	
	// 레벨에 배치된 전체 액터를 순회하면서 박스 찾기.
	for (Actor* const actor : actors)
	{
		// 액터가 박스 타입인지 확인.
		if (actor->IsTypeOf<Box>())
		{
			boxes.emplace_back(actor);
			continue;
		}
	}

	// 이동하려는 위치에 박스가 있는지 확인.
	Actor* boxActor = nullptr;
	for (Actor* const box : boxes)
	{
		// 위치 비교.
		if (box->GetPosition() == nextPosition)
		{
			boxActor = box;
			break;
		}
	}

	if (boxActor)
	{
		// #1 : 박스를 이동 시키려는 위치에 다른 박스가 또 있는지 확인.
		// 두 위치 사이에서 이동 방향 구하기.
		Vector2 direction = nextPosition - playerPosition;
		Vector2 newPosition = boxActor->GetPosition() + direction;

		// 검색
		for (Actor* const otherBox : boxes)
		{
			if (otherBox == boxActor)
				continue;

			if (otherBox->GetPosition() == newPosition)
			{
				return false;
			}
		}

		for (Actor* const actor : actors)
		{
			if (actor->GetPosition() == newPosition)
			{
				if (actor->IsTypeOf<Wall>())
					return false;


				// 그라운드 또는 타겟이면 이동 가능.
				if (actor->IsTypeOf<Ground>() || actor->IsTypeOf<Target>())
				{
					boxActor->SetPosition(newPosition);

					// 게임 점수 확인.
					isGameClear = CheckGameClear();

					return true;
				}
			}
		}

	}

	// 경우의 수 처리.
	// 이동하려는 곳에 박스가 있는 경우.

	// 이동하려는 곳에 박스가 없는 경우.
	// 이동하려는 곳에 있는 액터가 벽이 아니면 이동 가능.
	for (Actor* const actor : actors)
	{
		// 먼저, 이동하려는 위치에 있는 액터 검색.
		if (actor->GetPosition() == nextPosition)
		{
			// 이 액터가 벽인지 확인.
			if (actor->IsTypeOf<Wall>())
			{
				return false;
			}

			// 그라운드 또는 타겟.
			return true;
		}
	}
	
	// Error.
	return false;
}

bool SokobanLevel::CheckGameClear()
{
	// 타겟 위에 있는 박스의 수 검증.
	int currScore = 0;

	// 배열에 박스 및 타겟 저장.
	std::vector<Actor*> boxes;
	std::vector<Actor*> targets;

	// 레벨에 배치된 배열 순회하면서 두 액터 필터링.
	for (Actor* const actor : actors)
	{
		if (actor->IsTypeOf<Box>())
		{
			boxes.emplace_back(actor);
			continue;
		}
		
		// 타겟의 경우 타겟 배열에 추가.
		if (actor->IsTypeOf<Target>())
		{
			targets.emplace_back(actor);
		}
	}

	// 점수 확인 (박스의 위치가 타겟의 위치와 같은지 비교)
	for (Actor* const box : boxes)
	{
		for (Actor* const target : targets)
		{
			// 두 액터의 위치가 같으면 점수 +.
			if (box->GetPosition() == target->GetPosition())
			{
				currScore += 1;
			}
		}
	}

	return currScore == targetScore;
}
