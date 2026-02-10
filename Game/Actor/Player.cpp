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
#include "../Manager/GameManager.h"
#include "Enemy/Enemy.h"

#include <Windows.h>

using namespace Wanted;

Player::Player(const Vector2 position)
	: super("P", position, Color::BrightWhite)
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

	// bodyCollider
	{
		int left = static_cast<int>(position.x);
		int top = static_cast<int>(position.y);
		int right = left + GetWidth();
		int bottom = top + GetHeight();

		bodyCollider = new BoxCollider(left, top, right, bottom, 0, 0);
		bodyCollider->SetOnEnter([](BoxCollider* self, BoxCollider* other)
		{
			if (other->GetOwner()->IsTypeOf<Enemy>())
			{
				GameManager::Get().GameOver();
				self->GetOwner()->Destroy();
				return;
			}

			//if (self->GetOwner()->IsTypeOf<Snow>())
			//{
			//	Snow* snow = self->GetOwner()->As<Snow>();
			//	if (snow->GetMode() != Snow::ESnowMode::Projectile)
			//		return;

			//	snow->AddKillCount();

			//	// �߰����� ����.
			//	GameManager::Get().AddScore(snow->GetKillCount() * 1.6f);
			//}

			// damageable->OnDamaged((int)Enemy::EDamageType::Dead);
		});


		CollisionSystem::Get().Register(bodyCollider);
		AddNewComponent(bodyCollider);
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
	if (GameManager::Get().isGameOver)
		return;

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
