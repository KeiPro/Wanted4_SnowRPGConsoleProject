#include "Thief.h"
#include "Util/Util.h"
#include "Engine/Engine.h"
#include "Actor/Player.h"
#include "Level/Level.h"
#include "Manager/GameManager.h"
#include "Component/Collider/BoxCollider.h"
#include "Physics/CollisionSystem.h"

using namespace Wanted;

Thief::Thief(const Vector2 position)
	: super("T", position, Color::Red), initialPosition(position)
{
	chaseCount = Util::Random(3, 5);
	chaseRange = Util::Random(5, 8); // move 2~4 pixels

	moveSpeed = 5;

	// box¿« ≈©±‚ : 3 by 3
	int left = static_cast<int>(position.x) - 1;
	int top = static_cast<int>(position.y) - 1;
	int right = left + 3;
	int bottom = top + 3;

	bodyCollider = new BoxCollider(left, top, right, bottom, -1, -1);
	bodyCollider->debugMode = true;
	bodyCollider->debugColor = Color::Red;
	CollisionSystem::Get().Register(bodyCollider);
	AddNewComponent(bodyCollider);
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

	// UpdateChase 1.

	// UpdateChase 2.

	Vector2 targetPosition = player->GetPosition();

	moveDir = targetPosition.x - position.x >= 0.0f ? 1 : -1;
	float delta = moveSpeed * deltaTime * moveDir;
	position.x += delta;
}

void Thief::UpdateAttack(float deltaTime)
{

}

void Thief::Dead()
{
	Enemy::Dead();
}
