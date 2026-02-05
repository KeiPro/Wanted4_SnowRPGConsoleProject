#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
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


	float moveDirX = 0.0f;

	// 이동
	if (Input::Get().GetKey(VK_RIGHT))
		moveDirX += moveSpeed * deltaTime;

	if (Input::Get().GetKey(VK_LEFT))
		moveDirX -= moveSpeed * deltaTime;

	if (moveDirX != 0.0f)
		SetPosition(Vector2(position.x + moveDirX, position.y));
}

void Player::Draw()
{
	Actor::Draw();
}
