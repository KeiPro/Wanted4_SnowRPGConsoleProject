#include "MoveComponent.h"
#include "Actor/Actor.h"
#include "Component/Collider/BoxCollider.h"
#include "Actor/Player.h"
#include "Util/GameConstants.h"

using namespace Wanted;

MoveComponent::MoveComponent()
{
    jumpPower = sqrtf(2.0f * GameConst::Gravity * GameConst::JumpHeight);
}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::BeginPlay()
{
	Component::BeginPlay();
    physY = GetOwner()->GetPosition().y;
}

void MoveComponent::Tick(float deltaTime)
{
    Vector2 pos = GetOwner()->GetPosition();

    // Gravity
    if (!onGrounded)
        velocity.y += GameConst::Gravity * deltaTime;

    if (velocity.y > 0.0f &&
        footCollider->GetIsActive() == false)
		footCollider->SetIsActive(true);

    physY += velocity.y * deltaTime;
}

void MoveComponent::OnFootEnter(BoxCollider* ground, int floorY)
{
    groundContacts.insert(ground); 
    onGrounded = true;
    physY = floorY;
    velocity.y = 0.f;
    footCollider->SetIsActive(true);
}

void MoveComponent::OnFootExit(BoxCollider* ground)
{
    groundContacts.erase(ground);
    onGrounded = !groundContacts.empty();
}

void MoveComponent::Jump()
{
    // 박스 콜라이더 비활성화.
    footCollider->SetIsActive(false);

    velocity.y = -jumpPower;
    onGrounded = false;
}
