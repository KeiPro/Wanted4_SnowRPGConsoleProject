#pragma once

#include "Common/Common.h"
#include <Windows.h>

// SetConsoleTextAttribute()

namespace Wanted
{
	// 콘솔에 텍스트 색상 등을 지정할 때 사용할 색상 열거형
	enum class WANTED_API Color : unsigned short
	{
		Baclk = 0,
		Red = FOREGROUND_RED,
		Green = FOREGROUND_GREEN,
		Blue = FOREGROUND_BLUE,
		White = Blue | Green | Red,
	};
}