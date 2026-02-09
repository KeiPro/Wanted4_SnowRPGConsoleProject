#include "MoveComponent.h"
#include "Core/Input.h"
#include "Actor/Actor.h"
#include "Component/Collider/BoxCollider.h"
#include "Actor/Player.h"
#include "Engine/Engine.h"

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

    Vector2 pos = GetOwner()->GetPosition();

    // Move Left, Right 
    float dirX = 0.f;
    if (Input::Get().GetKey(VK_RIGHT)) dirX += 1.f;
    if (Input::Get().GetKey(VK_LEFT))  dirX -= 1.f;

    const int mapW = Engine::Get().GetWidth();
    const int minX = 1;
    const int maxX = mapW - 1;

    velocity.x = dirX * moveSpeed;

    float nextX = pos.x + velocity.x * deltaTime;
    if (nextX > minX && nextX < maxX)
        pos.x = nextX;

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
    pos.y = static_cast<int>(physY);

    GetOwner()->SetPosition(pos);

    Player* player = static_cast<Player*>(GetOwner());
    if (player == nullptr)
        return;

    if (velocity.x > 0.f)
        player->SetDir(Player::EDir::Right);
    else if (velocity.x < 0.f)
        player->SetDir(Player::EDir::Left);

    Vector2 newFirePos = {GetOwner()->GetPosition().x, GetOwner()->GetPosition().y};
    if (player->GetDir() == Player::EDir::Right)
        newFirePos.x += player->GetWidth();
    else
        newFirePos.x -= 1;

    player->SetFirePos(newFirePos);
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
