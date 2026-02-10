#pragma once

#include "Common/Common.h"
#include <Windows.h>

// SetConsoleTextAttribute()

namespace Wanted
{
	enum class WANTED_API Color : unsigned short
	{
		// ---------- Foreground ----------
		Black = 0,
		Red = FOREGROUND_RED,
		Green = FOREGROUND_GREEN,
		Blue = FOREGROUND_BLUE,
		White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,

		// ¹àÀº »ö (Intensity)
		BrightRed = Red | FOREGROUND_INTENSITY,
		BrightGreen = Green | FOREGROUND_INTENSITY,
		BrightBlue = Blue | FOREGROUND_INTENSITY,
		BrightWhite = White | FOREGROUND_INTENSITY,

		// ---------- Background ----------
		BgBlack = 0,
		BgRed = BACKGROUND_RED,
		BgGreen = BACKGROUND_GREEN,
		BgBlue = BACKGROUND_BLUE,
		BgWhite = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,

		// ¹àÀº ¹è°æ
		BgBrightRed = BgRed | BACKGROUND_INTENSITY,
		BgBrightGreen = BgGreen | BACKGROUND_INTENSITY,
		BgBrightBlue = BgBlue | BACKGROUND_INTENSITY,
		BgBrightWhite = BgWhite | BACKGROUND_INTENSITY,

		// ---------- Preset ----------
		WhiteOnRed = White | BgRed,
		BlackOnWhite = BgWhite,
		GreenOnBlack = Green,
		Warning = BrightWhite | BgBrightRed,
	};
}
