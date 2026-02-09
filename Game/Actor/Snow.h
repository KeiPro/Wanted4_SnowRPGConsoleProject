#pragma once
#include "Actor/Actor.h"
#include "Util/Timer.h"
#include "Interface/IDamageable.h"

namespace Wanted
{
    class Enemy;
    class BoxCollider;

    class Snow : public Actor, public IDamageable
    {
        RTTI_DECLARATIONS(Snow, Actor)

    public:
        struct FreezeEffect
        {
            const char* frame = ".";
            float meltTime = 1.0f;
            int hp = 2;
            Color color = Color::Blue;
        };

        enum class ESnowMode
        {
            Frozen,
            Projectile,
        };

    public:
        Snow(const Vector2& position, Enemy* changedEnemy);
        ~Snow() override = default;

        void Tick(float deltaTime) override;
        void Draw() override;

        // IDamageable
        void OnDamaged(int damage) override;

        // 외부에서 강제 발사하고 싶을 때
        void Launch(int dirX);

    private:
        void ApplyEffect(int index);
        void TickFrozen(float dt);
        void TickProjectile(float dt);

        void MeltOneStep();
        void GrowOneStep();

        void ReleaseSnowball();

        void BounceX();
        void KillProjectile();

        void SetCollidersActive_Frozen();
        void SetCollidersActive_Projectile();

    private:
        // State
        ESnowMode mode = ESnowMode::Frozen;
        bool isSnowballReleased = false;

        // Freeze Sequence
        Timer timer;
        int hp = 1;
        int freezeEffectSequenceCount = 0;
        int currentSequenceIndex = 0;

        // Projectile
        Vector2 velocity = {};
        int remainingBounces = 3;
        bool onGround = false;

        // projectile params
        float launchSpeedX = 3.0f;
        float launchSpeedY = -8.0f;

        int pendingLaunchDirX = 1;

        // refs
        Enemy* changedEnemy = nullptr;

        // colliders
        BoxCollider* bodyCollider = nullptr;
        BoxCollider* footCollider = nullptr;
    };
}
