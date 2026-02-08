#include "PlayerBullet.h"

#include <Windows.h>
#include <cmath>

using namespace Wanted;

PlayerBullet::PlayerBullet(const Vector2& position, Player::EDir dir)
    : super("*", position, Color::Blue)
    , dir(dir)
{
    sortingOrder = 10;
    velocity.x = (dir == Player::EDir::Right) ? moveSpeed : -moveSpeed;
    velocity.y = 0.0f;
}

PlayerBullet::~PlayerBullet() {}

void PlayerBullet::BeginPlay()
{
    Actor::BeginPlay();
    physX = GetPosition().x;
    physY = GetPosition().y;
}

void PlayerBullet::Tick(float deltaTime)
{
    Actor::Tick(deltaTime);

    float dt = deltaTime;
    if (dt > 0.05f) 
        dt = 0.05f;

    lifeTime += dt;
    if (lifeTime >= maxLifeTime)
    {
        lifeTime = 0.0f;
        Destroy();
        return;
    }

    physX += velocity.x * dt;

    // 중력 적용
    velocity.y += gravity * dt;
    physY += velocity.y * dt;

    // 위치 갱신
    Vector2 pos = GetPosition();
    pos.x = (int)physX;
    pos.y = (int)physY;

    SetPosition(pos);
}
