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
#include <cmath>

using namespace Wanted;

Thief::Thief(const Vector2 position)
	: super("T", position, Color::Red), initialPosition(position)
{
	chaseCount = 1;  Util::Random(3, 5);
	chaseRange = 1; Util::Random(5, 8); // move 2~4 pixels

	moveSpeed = 5;

	thiefMoveComp = new ThiefMoveComponent();
	AddNewComponent(thiefMoveComp);

	// bodyCollider -> box의 크기 : (width + 2, height + 2)
	{
		int left = static_cast<int>(position.x) - 1;
		int top = static_cast<int>(position.y) - 1;
		int right = left + GetWidth() + 2;
		int bottom = top + GetHeight() + 2;

		bodyCollider = new BoxCollider(left, top, right, bottom, -1, -1);
		bodyCollider->debugMode = true;
		bodyCollider->debugColor = Color::Red;
		CollisionSystem::Get().Register(bodyCollider);
		AddNewComponent(bodyCollider);
	}
	
	// footCollider -> box의 크기 : (width, 1)
	{
		// 초기 위치 설정.
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

		footCollider->debugMode = true;
		footCollider->debugColor = Color::Green;
		CollisionSystem::Get().Register(footCollider);
		AddNewComponent(footCollider);
	}
}

Thief::~Thief()
{

}

void Thief::BeginPlay()
{
	Enemy::BeginPlay();
}

void Thief::Tick(float deltaTime)
{
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
	// x축으로 일정 범위 안에 들어왔는지 체크.
	//    만약, 들어오지 않았다면 return;
	if (CheckPlayerXRange(position.x, targetPosition.x) == false)
		return;

	float diff = position.y - targetPosition.y;

	// 같은 위치에 있다.
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

	//if (position.y < targetPosition.y)
	//{
	//	// 아래로 점프.
	//	jumpElapsedTime = 0.0f;
	//	MoveComponent* moveComp = GetComponent<MoveComponent>();
	//}

	//// UpdateChase 2.
	//if (position.y < targetPosition.y)
	//{
	//	// 아래로 점프 진행.

	//}
	//else if (position.y > targetPosition.y)
	//{
	//	// 위로 점프 진행.		

	//}
}

void Thief::UpdateAttack(float deltaTime)
{

}

void Thief::Dead()
{
	Enemy::Dead();
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
