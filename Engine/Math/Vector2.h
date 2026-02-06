#pragma once

#include "Common/Common.h"
#include <Windows.h>

namespace Wanted
{
	class WANTED_API Vector2
	{
	public:

		Vector2();
		Vector2(int x, int y);
		Vector2(float x, float y);
		~Vector2();

		const char* ToString();

		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;
		Vector2 operator*(const float other) const;

		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;
		Vector2& operator+=(const Vector2& other);
		
		operator COORD() const;

		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Up;
		static Vector2 Right;

	public:
		float x = 0;
		float y = 0;

	private:
		char* string = nullptr;
	};
}