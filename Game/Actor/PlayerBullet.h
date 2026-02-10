#pragma once

#include "Actor/Actor.h"
#include "Player.h"
#include "Util/GameConstants.h"

namespace Wanted
{
    class BoxCollider;
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
        float gravity = GameConst::Gravity;
        Vector2 velocity = {};
        float physX = 0.f;
        float physY = 0.0f;

        float lifeTime = 0.0f;
        float maxLifeTime = 0.15f;
        BoxCollider* boxCollider = nullptr;
    };
}
