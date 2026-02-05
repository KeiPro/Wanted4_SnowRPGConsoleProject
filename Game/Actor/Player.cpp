#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Game/Game.h"
#include "Component/MoveComponent.h"
#include "Component/Collider/BoxCollider.h"

#include <Windows.h>

using namespace Wanted;

Player::Player(const Vector2 position)
	: super("<=A=>", position, Color::Red)
{
	sortingOrder = 10;

	AddNewComponent(new MoveComponent());
	/*AddNewComponent(new BoxCollider("FloorBoxCollider"));
	AddNewComponent(new BoxCollider("CollisionCollider"));*/
}

void Player::BeginPlay()
{
	Actor::BeginPlay();
}

void Player::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	if (Wanted::Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
		return;
	}
}

void Player::Draw()
{
	Actor::Draw();
}
