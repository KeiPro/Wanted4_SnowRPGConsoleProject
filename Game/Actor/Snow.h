#pragma once
#include "Actor/Actor.h"
#include "Util/Timer.h"
#include "Interface/IDamageable.h"

#include <unordered_set>

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

		void BeginPlay() override;
        void Tick(float deltaTime) override;
        void Draw() override;

		ESnowMode GetMode() const { return mode; }

        // IDamageable
        void OnDamaged(int damage) override;

        void Launch(int dirX);

        void OnFootEnter(BoxCollider* ground, int floorY);
        void OnFootExit(BoxCollider* ground);

    private:
        void ApplyEffect(int index);
        void TickFrozen(float dt);
        void TickProjectile(float dt);

        void MeltOneStep();
        void GrowOneStep();

        void ReleaseSnowball();

        void BounceX();
        void KillProjectile();

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
        float physY = 0.0f;
        int remainingBounces = 3;
        bool onGround = false;

        // projectile params
        float launchSpeedX = 80.0f;
        float launchSpeedY = -8.0f;

        int pendingLaunchDirX = 1;

        // refs
        Enemy* changedEnemy = nullptr;

        // colliders
        std::unordered_set<BoxCollider*> groundContacts;
        BoxCollider* bodyCollider = nullptr;
        BoxCollider* footCollider = nullptr;
    };
}
