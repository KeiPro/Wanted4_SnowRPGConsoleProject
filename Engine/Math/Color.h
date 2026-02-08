#pragma once

#include "Common/Common.h"
#include <Windows.h>

// SetConsoleTextAttribute()

namespace Wanted
{
	enum class WANTED_API Color : unsigned short
	{
		Baclk = 0,
		Red = FOREGROUND_RED,
		Green = FOREGROUND_GREEN,
		Blue = FOREGROUND_BLUE,
		White = Blue | Green | Red,
	};
}