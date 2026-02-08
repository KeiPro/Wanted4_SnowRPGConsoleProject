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
	: super("P", position, Color::Blue)
{
	sortingOrder = 10;

	AddNewComponent(new MoveComponent());

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

				moveComp->OnFootEnter(other);

				moveComp->RequestOnGrounded(other->GetOwner()->GetPosition().y - 1);
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

		footCollider->debugMode = true;

		AddNewComponent(footCollider);
		CollisionSystem::Get().Register(footCollider);
	}
}

void Wanted::Player::SetDir(EDir newDir)
{
	if (dir == newDir)
		return;

	EDir old = dir;
	dir = newDir;
	//OnChangedDir(old, newDir);
}

//void Wanted::Player::OnChangedDir(EDir oldDir, EDir newDir)
//{
//	if (auto* move = GetComponent<MoveComponent>())
//		move->ClearSideBlocks();
//
//	UpdateSideColliderOffset();
//}
//
//void Wanted::Player::UpdateSideColliderOffset()
//{
//	if (!sideCollider) 
//		return;
//
//	int w = GetWidth();
//	if (dir == EDir::Right)
//		sideCollider->SetOffset(w, 0);
//	else
//		sideCollider->SetOffset(-1, 0);
//}

void Player::BeginPlay()
{
	Actor::BeginPlay();
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
