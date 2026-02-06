#include "MoveComponent.h"
#include "Core/Input.h"
#include "Actor/Actor.h"
#include "Component/Collider/BoxCollider.h"

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

    physY = GetOwner()->GetPosition().y;

    BoxCollider* boxCollider = GetOwner()->GetComponent<BoxCollider>();

    floorBox = GetOwner()->GetComponent<BoxCollider>();
}

void MoveComponent::Tick(float deltaTime)
{
    const float gravity = 200.0f;
    const float jumpHeight = 3;
    const float jumpPower = sqrtf(2.0f * gravity * jumpHeight);

    float dt = deltaTime;
    if (dt > 0.05f) dt = 0.05f;
    elapsedTime += dt;

    onGrounded = (elapsedTime - lastGroundedTime) <= 0.03f;
    
    float dirX = 0.f;
    if (Input::Get().GetKey(VK_RIGHT)) dirX += 1.f;
    if (Input::Get().GetKey(VK_LEFT))  dirX -= 1.f;
    velocity.x = dirX * moveSpeed;

    // Jump
    if (Input::Get().GetKeyDown('S') && onGrounded)
    {
        lastGroundedTime = 0.0f;

        // 박스 콜라이더 비활성화.
        floorBox->SetIsActive(false);

        velocity.y = -jumpPower;
        onGrounded = false;
    }

    // Gravity
    if (!onGrounded)
        velocity.y += gravity * deltaTime;

    if (velocity.y > 0.0f &&
        floorBox->GetIsActive() == false)
		floorBox->SetIsActive(true);

    physY += velocity.y * deltaTime;

    Vector2 pos = GetOwner()->GetPosition();
    pos.x += velocity.x * deltaTime;       
    pos.y = static_cast<int>(physY);

    GetOwner()->SetPosition(pos);
}

void MoveComponent::RequestOnGrounded(int floorY)
{
    // 하강 중일때에만,
    if (velocity.y < 0)
        return;

    physY = floorY;
    onGrounded = true;
    velocity.y = 0.f;

    lastGroundedTime = elapsedTime;

    floorBox->SetIsActive(true);
}