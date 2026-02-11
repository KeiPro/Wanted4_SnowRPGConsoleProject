#include "Thief.h"
#include "Util/Util.h"
#include "Engine/Engine.h"
#include "Actor/Player.h"
#include "Level/Level.h"
#include "Manager/GameManager.h"
#include "Component/Collider/BoxCollider.h"
#include "Physics/CollisionSystem.h"
#include "Actor/Envrionments/En_Wall.h"
#include "Component/ThiefMoveComponent.h"
#include "Actor/Snow.h"

#include <cmath>

using namespace Wanted;

Thief::Thief(const Vector2 position)
	: super("T", position, Color::Red), initialPosition(position)
{
	chaseCount = Util::Random(3, 5);
	chaseRange = Util::Random(5, 8);

	moveSpeed = 5;

	thiefMoveComp = new ThiefMoveComponent();
	AddNewComponent(thiefMoveComp);

	// bodyCollider
	{
		int left = static_cast<int>(position.x) - 1;
		int top = static_cast<int>(position.y) - 1;
		int right = left + GetWidth() + 2;
		int bottom = top + GetHeight() + 2;

		bodyCollider = new BoxCollider(left, top, right, bottom, -1, -1);
		CollisionSystem::Get().Register(bodyCollider);
		AddNewComponent(bodyCollider);
	}
	
	// footCollider
	{
		int left = static_cast<int>(position.x);
		int top = static_cast<int>(position.y) + 1;
		int right = left + GetWidth();
		int bottom = top + 1;
	
		footCollider = new BoxCollider(left, top, right, bottom, 0, 1);
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

		CollisionSystem::Get().Register(footCollider);
		AddNewComponent(footCollider);
	}
}

Thief::~Thief()
{

}

void Thief::OnDamaged(int damage)
{
	if (state == EnemyState::Freeze)
		return;

	Enemy::OnDamaged(damage);

	if (bodyCollider)
		bodyCollider->SetIsActive(false);

	if (state == EnemyState::Dead)
		return;

	ownerSnow = new Snow(GetPosition(), this);
	GetOwner()->AddNewActor(ownerSnow);
}

void Thief::BeginPlay()
{
	Enemy::BeginPlay();
}

void Thief::Tick(float deltaTime)
{
	if (GameManager::Get().isGameOver)
		return;

	Enemy::Tick(deltaTime);
}

void Thief::Draw()
{
	Enemy::Draw();
}

void Thief::UpdateIdle(float deltaTime)
{
	Enemy::UpdateIdle(deltaTime);

	if (chaseCount <= 0)
	{
		state = EnemyState::Chase;
		return;
	}

	const float minX = 1;
	const float maxX = Engine::Get().GetWidth() - 1;
	
	int nextTargetPos = initialPosition.x + moveDir * chaseRange;
	if (nextTargetPos < minX)
		nextTargetPos = minX + 1;
	else if (nextTargetPos > maxX)
		nextTargetPos = minX - 1;

	float delta = moveSpeed * deltaTime * moveDir;
	if (moveDir > 0 && position.x + delta > nextTargetPos)
	{
		position.x = nextTargetPos;
		needChangeDir = true;
	}
	else if (moveDir < 0 && position.x + delta < nextTargetPos)
	{
		position.x = nextTargetPos;
		needChangeDir = true;
	}
	else
	{
		position.x += delta;
	}

	if (needChangeDir)
	{
		elapsedTime += deltaTime;
		if (elapsedTime < changeDirInterval)
			return;

		elapsedTime = 0.0f;
		moveDir = moveDir * -1;
		chaseCount--;
		needChangeDir = false;
	}
}

void Thief::UpdateChase(float deltaTime)
{
	Player* player = GameManager::Get().GetPlayer();
	if (!player)
		return;
	
	Vector2 targetPosition = player->GetPosition();
	moveDir = targetPosition.x - position.x >= 0.0f ? 1 : -1;
	float delta = moveSpeed * deltaTime * moveDir;
	position.x += delta;

	// UpdateChase 1.
	// x axis
	if (CheckPlayerXRange(position.x, targetPosition.x) == false)
		return;

	float diff = position.y - targetPosition.y;

	if (abs(diff) <= 0.00001f)
		return;

	jumpElapsedTime += deltaTime;
	if (jumpElapsedTime < jumpInterval)
		return;

	if (position.y > targetPosition.y)
	{
		jumpElapsedTime = 0.0f;
		
		if (thiefMoveComp && thiefMoveComp->IsOnGrounded())
		{
			thiefMoveComp->Jump();
		}
	}
}

void Thief::UpdateAttack(float deltaTime)
{

}

void Thief::Dead()
{
	Enemy::Dead();

	GameManager::Get().AddScore(20);

	if (ownerSnow)
	{
		ownerSnow->ClearOwnedEnemy(this);
		ownerSnow = nullptr;
	}
}

void Thief::OnSnowballReleased(const Vector2& position)
{
	Enemy::OnSnowballReleased(position);
	bodyCollider->SetIsActive(true);

	if (ownerSnow)
	{
		ownerSnow->ClearOwnedEnemy(this);
		ownerSnow = nullptr;
	}
}

bool Thief::CheckPlayerXRange(float myPosX, float playerPosX)
{
	if (myPosX < playerPosX - 2.0f ||
		myPosX > playerPosX + 2.0f)
	{
		return false;
	}

	return true;
}
