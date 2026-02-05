#include "MoveComponent.h"
#include "Core/Input.h"
#include "Actor/Actor.h"

#include <Windows.h>

using namespace Wanted;

MoveComponent::MoveComponent()
{

}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::BeginPlay()
{
	Component::BeginPlay();
}

void MoveComponent::Tick(float deltaTime)
{
	float moveDirX = 0.0f;

	// ÀÌµ¿
	if (Input::Get().GetKey(VK_RIGHT))
		moveDirX += moveSpeed * deltaTime;

	if (Input::Get().GetKey(VK_LEFT))
		moveDirX -= moveSpeed * deltaTime;

	velocity.x = moveDirX;
	if (Input::Get().GetKey('S'))
	{
		if (onGrounded)
		{
			velocity.y = -jumpPower;
			onGrounded = false;
		}
	}

	if (onGrounded == false)
		velocity.y += 20 * deltaTime;

	Vector2 newPosition = GetOwner()->GetPosition() + velocity;

	GetOwner()->SetPosition(newPosition);
}
