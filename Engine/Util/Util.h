#pragma once

#include "Math/Vector2.h"
#include "Math/Color.h"
#include <time.h>

using namespace Wanted;

// 헬퍼(Helper) 기능 제공.
namespace Util
{
	// 콘솔 커서 위치 이동(설정)하는 함수.
	inline void SetConsolePosition(const Vector2& position)
	{
		SetConsoleCursorPosition(
			GetStdHandle(STD_OUTPUT_HANDLE),
			static_cast<COORD>(position)
		);
	}

	inline void SetConsoleTextColor(Color color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<unsigned short>(color));
	}

	// 커서 끄기.
	inline void TurnOffCursor()
	{
		CONSOLE_CURSOR_INFO info = {};

		GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info); // 커서 정보 가져와서 설정하기.

		info.bVisible = false;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	}

	// 커서 켜기.
	inline void TurnOnCursor()
	{
		CONSOLE_CURSOR_INFO info = {};

		GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info); // 커서 정보 가져와서 설정하기.

		info.bVisible = true;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	}

	// 정수 난수 함수.
	inline int Random(int min, int max)
	{
		int diff = (max - min) + 1;
		return ((diff * rand()) / (RAND_MAX + 1)) + min;
	}

	inline void SetRandomSeed()
	{
		srand(static_cast<unsigned int>(time(nullptr)));
	}

	// 부동소수점 난수 함수.
	inline float RandomRange(float min, float max)
	{
		// 0 ~ 1 사이의 float 기반 랜덤값.
		float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

		float diff = (max - min);
		return (random * diff) + min;
	}
};

// 메모리 정리 함수.
template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}

template<typename T>
void SafeDeleteArray(T*& t)
{
	if (t)
	{
		delete[] t;
		t = nullptr;
	}
}