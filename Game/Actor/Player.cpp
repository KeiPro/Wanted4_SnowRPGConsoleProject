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
	: super("P", position, Color::Red)
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
		//if (input->GetKeyDown(VK_ESCAPE))
		//{
		//	QuitEngine();
		//}


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

	// static을 붙이면 데이터 영역에 저장. 
	// 맨 처음에 메모리에 잡혀있지 않을 때 한 번 호출되며 데이터 영역에 저장.
	// 하지만 변수는 이 함수 안에서만 접근 가능.
	// (멤버변수로 두고 BeginPlay에서 한 번 호출해서 사용하는 방법도 있음)
	static ICanPlayerMove* canPlayerMoveInterface = nullptr;

	// 오너십 확인(null 확인).
	if (!canPlayerMoveInterface && GetOwner())
	{
		canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());
	}

	//std::cout << "TestActor::Tick(). deltaTime: " << deltaTime << ", FPS : " << (1.0f / deltaTime) << "\n";
	// 이동
	if (Input::Get().GetKeyDown('D') && GetPosition().x < 20)
	{
		// 이동 가능 여부 판단.
		Vector2 newPosition(GetPosition().x + 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		//Vector2 newPosition = GetPosition();
		//newPosition.x += 1;
		//SetPosition(newPosition);
	}

	if (Input::Get().GetKeyDown('A') && GetPosition().x > 0)
	{
		Vector2 newPosition(GetPosition().x - 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		//Vector2 newPosition = GetPosition();
		//newPosition.x -= 1;
		//SetPosition(newPosition);
	}

	if (Input::Get().GetKeyDown('S') && GetPosition().y < 15)
	{
		Vector2 newPosition(GetPosition().x, GetPosition().y + 1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}


		//Vector2 newPosition = GetPosition();
		//newPosition.y += 1;
		//SetPosition(newPosition);
	}

	if (Input::Get().GetKeyDown('W') && GetPosition().y > 0)
	{
		Vector2 newPosition(GetPosition().x, GetPosition().y - 1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition);
		}

		/*Vector2 newPosition = GetPosition();
		newPosition.y -= 1;
		SetPosition(newPosition);*/
	}
}

void Player::Draw()
{
	Actor::Draw();
}
