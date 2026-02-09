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

            struct FreezeEffect
        {
            const char* frame = ".";
            float meltTime = 0.05f;
            int hp = 2;
            Color color = Color::Blue;
        };

    public:
        Snow(const Vector2& position, Enemy* changedEnemy);
        ~Snow() override = default;

        void Tick(float deltaTime) override;
        void Draw() override;

        void OnDamaged(int damage) override;

    private:
        void ApplyEffect(int index);
        void GrowOneStep();     // 피해로 커짐
        void MeltOneStep();     // 시간으로 녹음
        void ReleaseSnowball(); // 완전히 녹아서 enemy 복구

    private:
        Timer timer;
        int hp = 1;

        int currentSequenceIndex = 0;
        int freezeEffectSequenceCount = 0;

        Enemy* changedEnemy = nullptr; // (가능하면 약한 참조/ID로 바꾸는게 더 안전)
        bool isSnowballReleased = false;

        BoxCollider* bodyCollider = nullptr;
    };
}
