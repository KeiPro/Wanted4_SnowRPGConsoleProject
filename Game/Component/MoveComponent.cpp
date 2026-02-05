#include "MoveComponent.h"
#include "Core/Input.h"
#include "Actor/Actor.h"

#include <Windows.h>
#include <cmath>

using namespace Wanted;

MoveComponent::MoveComponent()
{
 
}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::BeginPlay()
{
    physY = GetOwner()->GetPosition().y;
	Component::BeginPlay();
}

void MoveComponent::Tick(float deltaTime)
{
    const float gravity = 200.0f;
    const float jumpHeight = 3;
    const float jumpPower = sqrtf(2.0f * gravity * jumpHeight);

    float dirX = 0.f;
    if (Input::Get().GetKey(VK_RIGHT)) dirX += 1.f;
    if (Input::Get().GetKey(VK_LEFT))  dirX -= 1.f;
    velocity.x = dirX * moveSpeed;

    // Jump
    if (Input::Get().GetKeyDown('S') && onGrounded)
    {
        velocity.y = -jumpPower;
        onGrounded = false;
    }

    // Gravity
    if (!onGrounded)
        velocity.y += gravity * deltaTime;

    physY += velocity.y * deltaTime;

    // 바닥 충돌
    //const float groundY = 17.f;
    //if (physY >= groundY)
    //{
    //    physY = groundY;
    //    velocity.y = 0.f;
    //    onGrounded = true;
    //}

    Vector2 pos = GetOwner()->GetPosition();
    pos.x += velocity.x * deltaTime;       
    pos.y = static_cast<int>(physY);

    GetOwner()->SetPosition(pos);
}
