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
    float gravity = 200.0f;
    float jumpHeight = 0.5f;

    float jumpPower = sqrtf(2.0f * gravity * jumpHeight);

    // 좌우 이동
    float dirX = 0.f;
    if (Input::Get().GetKey(VK_RIGHT)) dirX += 1.f;
    if (Input::Get().GetKey(VK_LEFT))  dirX -= 1.f;

    velocity.x = dirX * moveSpeed;

    // 점프
    if (Input::Get().GetKeyDown('S') && onGrounded)
    {
        velocity.y = -jumpPower;
        onGrounded = false;
    }

    // 중력s
    if (!onGrounded)
        velocity.y += gravity * deltaTime;

    // 이동
    Vector2 pos = GetOwner()->GetPosition();
    pos += velocity * deltaTime;

    // 바닥 충돌 (예시)
    if (pos.y >= 17)
    {
        pos.y = 17;
        velocity.y = 0.0f;
        onGrounded = true;
    }

    pos.y = static_cast<int>(pos.y);
    GetOwner()->SetPosition(pos);
}
