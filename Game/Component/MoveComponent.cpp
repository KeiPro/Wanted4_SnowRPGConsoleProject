#include "MoveComponent.h"
#include "Core/Input.h"
#include "Actor/Actor.h"
#include "Component/Collider/BoxCollider.h"
#include "Actor/Player.h"

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
    footCollider = GetOwner()->As<Player>()->GetFootCollider();
}

void MoveComponent::Tick(float deltaTime)
{
    const float gravity = 200.0f;
    const float jumpHeight = 3;
    const float jumpPower = sqrtf(2.0f * gravity * jumpHeight);

    float dt = deltaTime;
    if (dt > 0.05f) dt = 0.05f;
    
    // Move Left, Right 
    float dirX = 0.f;
    if (Input::Get().GetKey(VK_RIGHT)) dirX += 1.f;
    if (Input::Get().GetKey(VK_LEFT))  dirX -= 1.f;
    velocity.x = dirX * moveSpeed;

    Player* player = static_cast<Player*>(GetOwner());
    if (player)
    {
        if (velocity.x > 0.f)     
            player->SetDir(Player::EDir::Right);
        else if (velocity.x < 0.f)
            player->SetDir(Player::EDir::Left);
    }

    if (velocity.x < 0 && blockMoveLeft)
        velocity.x = 0;
    if (velocity.x > 0 && blockMoveRight)
        velocity.x = 0;

    // Jump
    if (Input::Get().GetKeyDown('S') && onGrounded)
    {
        // 박스 콜라이더 비활성화.
        footCollider->SetIsActive(false);
        
        velocity.y = -jumpPower;
        onGrounded = false;
    }

    // Gravity
    if (!onGrounded)
        velocity.y += gravity * deltaTime;

    if (velocity.y > 0.0f &&
        footCollider->GetIsActive() == false)
		footCollider->SetIsActive(true);

    physY += velocity.y * deltaTime;

    Vector2 pos = GetOwner()->GetPosition();
    pos.x += velocity.x * deltaTime;       
    pos.y = static_cast<int>(physY);

    GetOwner()->SetPosition(pos);
}

void MoveComponent::RequestOnGrounded(int floorY)
{
    physY = floorY;
    velocity.y = 0.f;
    footCollider->SetIsActive(true);
}

void MoveComponent::OnFootEnter(BoxCollider* ground)
{
    groundContacts.insert(ground); 
    onGrounded = true;
}

void MoveComponent::OnFootExit(BoxCollider* ground)
{
    groundContacts.erase(ground);
    onGrounded = !groundContacts.empty();
}
