#include "MenuLevel.h"
#include "Game/Game.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Render/Renderer.h"
#include <iostream>

MenuLevel::MenuLevel()
{
	// �޴� ������ ����
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
	// �޴� ������ ����.
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

	// �Է� ó�� (����Ű ��/�Ʒ�Ű, ����Ű, ESC)
	// �迭 ����.
	static int length = items.size();
	if (Input::Get().GetKeyDown('W'))
	{
		currentIndex = (currentIndex + length - 1) % length;
	}

	if (Input::Get().GetKeyDown('S'))
	{
		// �ε��� ������
		currentIndex = (currentIndex + 1) % length;
	}
	
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// �޴� �������� ������ �Լ� ������ ȣ��.
		items[currentIndex]->onSelected();
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		// �޴� ���
		Game::Get().ToggleMenu();

		// �ε��� �ʱ�ȭ
		currentIndex = 0;
	}
}

void MenuLevel::Draw()
{
	// �޴� ���� ���.
	//Util::SetConsolePosition(Vector2::Zero);
	//Util::SetConsoleTextColor(Color::White);

	//// �ؽ�Ʈ ���.
	//std::cout << "Sokoban Game\n\n";

	Renderer::Get().Submit("Sokoban Game", Vector2::Zero);

	// �޴� ������ ���.
	for (int i = 0; i < static_cast<int>(items.size()); i++)
	{
		// ������ ���� Ȯ��(���õƴ��� ����).
		Color textColor = (i == currentIndex) ? selectedColor : unselectedColor;

		Renderer::Get().Submit(items[i]->text, Vector2(0, 2 + i), textColor);

		// ���� ����.
		// Util::SetConsoleTextColor(textColor);

		// �ؽ�Ʈ ���.
		// std::cout << items[i]->text << "\n";
	}
}
