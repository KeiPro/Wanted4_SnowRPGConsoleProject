#pragma once

#include "Actor/Actor.h"
#include "Player.h"

namespace Wanted
{
    class PlayerBullet : public Actor
    {
        RTTI_DECLARATIONS(PlayerBullet, Actor)

    public:
        PlayerBullet(const Vector2& position, Player::EDir dir);
        ~PlayerBullet();

        virtual void BeginPlay() override;
        virtual void Tick(float deltaTime) override;

    private:
        Player::EDir dir;

        float moveSpeed = 50.0f;

        // gravity
        float gravity = 200.0f;
        Vector2 velocity = {};
        float physX = 0.f;
        float physY = 0.0f;

        float lifeTime = 0.0f;
        float maxLifeTime = 3.0f;
    };
}
