#include "ThiefMoveComponent.h"
#include "Actor/Actor.h"
#include "Actor/Enemy/Thief.h"

using namespace Wanted;

ThiefMoveComponent::ThiefMoveComponent()
{
	
}

ThiefMoveComponent::~ThiefMoveComponent()
{
}

void ThiefMoveComponent::BeginPlay()
{
	MoveComponent::BeginPlay();

	footCollider = GetOwner()->As<Thief>()->GetFootCollider();
}

void ThiefMoveComponent::Tick(float deltaTime)
{
	MoveComponent::Tick(deltaTime);

	Vector2 pos = GetOwner()->GetPosition();
	pos.y = static_cast<int>(physY);
	GetOwner()->SetPosition(pos);
}

void ThiefMoveComponent::Jump()
{
	MoveComponent::Jump();
}


