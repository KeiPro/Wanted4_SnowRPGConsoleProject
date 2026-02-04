#include "MenuLevel.h"
#include "Game/Game.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Render/Renderer.h"
#include <iostream>

MenuLevel::MenuLevel()
{
	// 메뉴 아이템 생성
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
	// 메뉴 아이템 제거.
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

	// 입력 처리 (방향키 위/아래키, 엔터키, ESC)
	// 배열 길이.
	static int length = items.size();
	if (Input::Get().GetKeyDown('W'))
	{
		currentIndex = (currentIndex + length - 1) % length;
	}

	if (Input::Get().GetKeyDown('S'))
	{
		// 인덱스 돌리기
		currentIndex = (currentIndex + 1) % length;
	}
	
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// 메뉴 아이템이 저장한 함수 포인터 호출.
		items[currentIndex]->onSelected();
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		// 메뉴 토글
		Game::Get().ToggleMenu();

		// 인덱스 초기화
		currentIndex = 0;
	}
}

void MenuLevel::Draw()
{
	// 메뉴 제목 출력.
	//Util::SetConsolePosition(Vector2::Zero);
	//Util::SetConsoleTextColor(Color::White);

	//// 텍스트 출력.
	//std::cout << "Sokoban Game\n\n";

	Renderer::Get().Submit("Sokoban Game", Vector2::Zero);

	// 메뉴 아이템 출력.
	for (int i = 0; i < static_cast<int>(items.size()); i++)
	{
		// 아이템 색상 확인(선택됐는지 여부).
		Color textColor = (i == currentIndex) ? selectedColor : unselectedColor;

		Renderer::Get().Submit(items[i]->text, Vector2(0, 2 + i), textColor);

		// 색상 설정.
		// Util::SetConsoleTextColor(textColor);

		// 텍스트 출력.
		// std::cout << items[i]->text << "\n";
	}
}
