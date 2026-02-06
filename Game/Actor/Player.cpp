#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Game/Game.h"
#include "Component/MoveComponent.h"
#include "Component/Collider/BoxCollider.h"
#include "Envrionments/En_Wall.h"
#include "Physics/CollisionSystem.h"
#include "Common/RTTI.h"

#include <Windows.h>

using namespace Wanted;

Player::Player(const Vector2 position)
	: super("<=A=>", position, Color::Red)
{
	sortingOrder = 10;

	AddNewComponent(new MoveComponent());

	int left = static_cast<int>(position.x);
	int top = static_cast<int>(position.y);
	int right = left + GetWidth();
	int bottom = top + GetHeight();

	//위치 재설정.
	BoxCollider* footCollider = new BoxCollider(left, bottom, right, bottom + 1, 0, 1);
	footCollider->SetCollisionCallback([](BoxCollider* self, BoxCollider* other)
		{
			if (other->GetOwner()->IsTypeOf<En_Wall>())
			{
				MoveComponent* const moveComp = self->GetOwner()->GetComponent<MoveComponent>();
				if (moveComp && moveComp->HasBeganPlay() && moveComp->IsOnGrounded() == false)
					moveComp->RequestOnGrounded(other->GetOwner()->GetPosition().y - 1);
			}
		});

	footCollider->debugMode = true;

	AddNewComponent(footCollider);
	CollisionSystem::Get().Register(footCollider);

	/*AddNewComponent(new BoxCollider());
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
