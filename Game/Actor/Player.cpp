#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Actor/Box.h"
#include "Level/Level.h"

#include "Game/Game.h"

#include "Interface/ICanPlayerMove.h"

#include <iostream>
#include <Windows.h>

using namespace Wanted;

Player::Player(const Vector2 position)
	: super("<=A=>", position, Color::Red)
{
	// 그리기 우선순위 높게 설정.
	sortingOrder = 10;
}

void Player::BeginPlay()
{
	// 상위 함수 호출.
	// c++는 부모 함수 가리키는 포인터가 없음.
	Actor::BeginPlay();
}

void Player::Tick(float deltaTime)
{
	// ESC키 처리.
	if (Wanted::Input::Get().GetKeyDown(VK_ESCAPE))
	{
		// 메뉴 활성화.
		Game::Get().ToggleMenu();
		return;
	}

	if (Input::Get().GetKeyDown('Q'))
	{
		Engine::Get().QuitEngine();
	}

	// 스페이스로 박스 생성.
	if (Input::Get().GetKeyDown(VK_SPACE))
	{
		// 박스 생성.
		if (owner)
		{
			owner->AddNewActor(new Box(GetPosition()));
		}
	}
	
	static ICanPlayerMove* canPlayerMoveInterface = nullptr;

	// 오너십 확인(null 확인).
	if (!canPlayerMoveInterface && GetOwner())
	{
		canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());
	}

	// 이동
	if (Input::Get().GetKeyDown('D') && GetPosition().x < 20)
	{
		// 이동 가능 여부 판단.
		Vector2 newPosition(GetPosition().x + 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}
	}

	if (Input::Get().GetKeyDown('A') && GetPosition().x > 0)
	{
		Vector2 newPosition(GetPosition().x - 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}
	}

	if (Input::Get().GetKeyDown('S') && GetPosition().y < 15)
	{
		Vector2 newPosition(GetPosition().x, GetPosition().y + 1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}
	}

	if (Input::Get().GetKeyDown('W') && GetPosition().y > 0)
	{
		Vector2 newPosition(GetPosition().x, GetPosition().y - 1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}
	}
}

void Player::Draw()
{
	Actor::Draw();
}
