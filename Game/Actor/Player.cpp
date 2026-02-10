#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Game/Game.h"
#include "Component/MoveComponent.h"
#include "Component/PlayerMoveComponent.h"
#include "Component/AttackComponent.h"
#include "Component/Collider/BoxCollider.h"
#include "Envrionments/En_Wall.h"
#include "Physics/CollisionSystem.h"

#include <Windows.h>

using namespace Wanted;

Player::Player(const Vector2 position)
	: super("P", position, Color::White)
{
	sortingOrder = 10;

	AddNewComponent(new PlayerMoveComponent());

	// footCollider
	{
		int left = static_cast<int>(position.x);
		int top = static_cast<int>(position.y);
		int right = left + GetWidth();
		int bottom = top + GetHeight();

		footCollider = new BoxCollider(left, bottom, right, bottom + 1, 0, 1);
		footCollider->SetOnEnter([](BoxCollider* self, BoxCollider* other)
		{
			if (!other->GetOwner()->IsTypeOf<En_Wall>())
				return;

			MoveComponent* const moveComp = self->GetOwner()->GetComponent<MoveComponent>();
			if (!moveComp || !moveComp->HasBeganPlay())
				return;

			moveComp->OnFootEnter(other, other->GetOwner()->GetPosition().y - 1);
		});

		footCollider->SetOnExit([](BoxCollider* self, BoxCollider* other)
		{
			if (!other->GetOwner()->IsTypeOf<En_Wall>())
				return;

			MoveComponent* const moveComp = self->GetOwner()->GetComponent<MoveComponent>();
			if (!moveComp)
				return;

			moveComp->OnFootExit(other);
		});

		//footCollider->debugMode = true;

		AddNewComponent(footCollider);
		CollisionSystem::Get().Register(footCollider);
	}

	// AttackComponent
	{
		attackComponent = new AttackComponent();
		AddNewComponent(attackComponent);
	}
}

void Wanted::Player::SetDir(EDir newDir)
{
	if (dir == newDir)
		return;

	dir = newDir;
}

void Player::BeginPlay()
{
	Actor::BeginPlay();

	attackComponent->SetSpawner(GetOwner());
}

void Player::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
		return;
	}
}

void Player::Draw()
{
	Actor::Draw();
}
