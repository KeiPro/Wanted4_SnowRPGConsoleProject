#include "SnowRPGLevel.h"
#include "Actor/Player.h"
#include "Core/Input.h"
#include "Actor/Envrionments/En_Wall.h"
#include "Actor/Envrionments/En_Empty.h"
#include "Util/Util.h"

#include <iostream>

/*
# : 벽(Wall)
. : 바닥(Ground)
p : 플레이어
b : 박스
t : 타겟.
*/

SnowRPGLevel::SnowRPGLevel()
{
	LoadMap("TestMap.txt");
}

void SnowRPGLevel::Draw()
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

void SnowRPGLevel::LoadMap(const char* filename)
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
	//12 22 
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

	// 사용한 버퍼 해제.
	delete[] data;

	// 파일이 정상적으로 열렸으면 닫기.
	fclose(file);
}

bool SnowRPGLevel::CheckGameClear()
{
	return false;
}
