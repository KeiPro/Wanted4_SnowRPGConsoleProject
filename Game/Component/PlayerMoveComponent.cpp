#include "PlayerMoveComponent.h"
#include "Component/MoveComponent.h"
#include "Actor/Actor.h"
#include "Actor/Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"

using namespace Wanted;

PlayerMoveComponent::PlayerMoveComponent()
{

}

PlayerMoveComponent::~PlayerMoveComponent()
{

}

void PlayerMoveComponent::BeginPlay()
{
	MoveComponent::BeginPlay();

	footCollider = GetOwner()->As<Player>()->GetFootCollider();
}

void PlayerMoveComponent::Tick(float deltaTime)
{
    MoveComponent::Tick(deltaTime);

    Vector2 pos = GetOwner()->GetPosition();
    const int mapW = Engine::Get().GetWidth();
    const int minX = 1;
    const int maxX = mapW - 1;

    float dirX = 0.f;
    if (Input::Get().GetKey(VK_RIGHT))
        dirX += 1.f;

    if (Input::Get().GetKey(VK_LEFT))
        dirX -= 1.f;                                         

    velocity.x = dirX * moveSpeed;
    float nextX = pos.x + velocity.x * deltaTime;
    if (nextX > minX && nextX < maxX)
        pos.x = nextX;

    if (Input::Get().GetKeyDown('S') && onGrounded)
        Jump();

    pos.y = static_cast<int>(physY);
    GetOwner()->SetPosition(pos);

    Player* player = static_cast<Player*>(GetOwner());
    if (player == nullptr)
        return;

    if (velocity.x > 0.f)
        player->SetDir(Player::EDir::Right);
    else if (velocity.x < 0.f)
        player->SetDir(Player::EDir::Left);

    Vector2 newFirePos = { GetOwner()->GetPosition().x, GetOwner()->GetPosition().y };
    if (player->GetDir() == Player::EDir::Right)
        newFirePos.x += player->GetWidth();
    else
        newFirePos.x -= 1;

    player->SetFirePos(newFirePos);
}
