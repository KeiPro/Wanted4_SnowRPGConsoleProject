#include "MenuLevel.h"
#include "Game/Game.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Render/Renderer.h"
#include <iostream>

MenuLevel::MenuLevel()
{
	items.emplace_back(
		new MenuItem(
			"Resume Game", []() {
				Game::Get().ToggleMenu();
			}
		)
	);

	items.emplace_back(
		new MenuItem(
			"Quit Game", []() {
				Game::Get().QuitEngine();
			}
		)
	);
}

MenuLevel::~MenuLevel()
{
	for (MenuItem*& item : items)
	{
		delete item;
		item = nullptr;
	}

	items.clear();
}

void MenuLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	static int length = items.size();
	if (Input::Get().GetKeyDown('W'))
	{
		currentIndex = (currentIndex + length - 1) % length;
	}

	if (Input::Get().GetKeyDown('S'))
	{
		currentIndex = (currentIndex + 1) % length;
	}
	
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		items[currentIndex]->onSelected();
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();

		currentIndex = 0;
	}
}

void MenuLevel::Draw()
{
	Renderer::Get().Submit("Sokoban Game", Vector2::Zero);

	for (int i = 0; i < static_cast<int>(items.size()); i++)
	{
		Color textColor = (i == currentIndex) ? selectedColor : unselectedColor;

		Renderer::Get().Submit(items[i]->text, Vector2(0, 2 + i), textColor);
	}
}
