#pragma once

#include "Level/Level.h"
#include "Math/Color.h"
#include <vector>

using namespace Wanted;

struct MenuItem
{
	using OnSelected = void (*)();

	MenuItem(const char* text, OnSelected onSelected)
		: onSelected(onSelected)
	{
		size_t length = strlen(text) + 1;
		this->text = new char[length];
		strcpy_s(this->text, length, text);
	}

	~MenuItem()
	{
		if (text)
		{
			delete[] text;
			text = nullptr;
		}
	}

	char* text = nullptr;

	OnSelected onSelected = nullptr;
};

class MenuLevel : public Level
{
	RTTI_DECLARATIONS(MenuLevel, Level)

public:
	MenuLevel();
	~MenuLevel();

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:
	int currentIndex = 0;

	Color selectedColor = Color::Green;

	Color unselectedColor = Color::White;

	std::vector<MenuItem*> items;
};
