#pragma once
#include "Actor/Actor.h"
#include "Util/Timer.h"
#include "Interface/IDamageable.h"
#include "Enemy/Enemy.h"

#include <unordered_set>
#include <vector>

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
        virtual void OnDestroy() override;

        void GiveKillReward(const Vector2& effectPos);
        void CaptureEnemy(Enemy* enemy) { capturedEnemy = enemy; }
        Enemy* GetCapturedEnemy() const { return capturedEnemy; }

        void KillCapturedEnemyAsDead()
        {
            if (!capturedEnemy)
                return;

            if (IDamageable* d = dynamic_cast<IDamageable*>(capturedEnemy))
            {
                d->OnDamaged((int)Enemy::EDamageType::Dead);
            }

            capturedEnemy = nullptr;
        }

        inline void AddKillCount() { killCount++; }

        inline int GetKillCount() const { return killCount; }
		ESnowMode GetMode() const { return mode; }
        
        // IDamageable
        void OnDamaged(int damage) override;

        void Launch(int dirX);
        void KillOwnedEnemy();

        void OnFootEnter(BoxCollider* ground, int floorY);
        void OnFootExit(BoxCollider* ground);
        bool IsSnowSizeMaxed() const 
        { 
            return (currentSequenceIndex >= freezeEffectSequenceCount - 1);
        }

    private:
        void ApplyEffect(int index);
        void TickFrozen(float dt);
        void TickProjectile(float dt);

        void MeltOneStep();
        void GrowOneStep(int dir);

        void ReleaseSnowball();

        void BounceX(int add = 0);
        void KillProjectile();

    public:

        bool alreadyMaximumSizeCollision = false;

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
        int remainingBounces = 5;
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

        int killCount = 0;

        Enemy* capturedEnemy = nullptr;
    };
}
