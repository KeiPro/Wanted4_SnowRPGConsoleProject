#include "Snow.h"
#include "Actor/Enemy/Enemy.h"
#include "Component/Collider/BoxCollider.h"
#include "Physics/CollisionSystem.h"

using namespace Wanted;

static const Snow::FreezeEffect sequence[] =
{
    {".", 1.0f, 2, Color::Blue},
    {"o", 1.5f, 2, Color::Blue},
    {"O", 2.0f, 2, Color::Blue},
    {"Q", 2.0f, 2, Color::Blue},
    {"@", 3.0f, 2, Color::Blue},
};

Snow::Snow(const Vector2& position, Enemy* changedEnemy)
    : super(sequence[0].frame, position, sequence[0].color)
    , changedEnemy(changedEnemy)
{
    sortingOrder = 10;

    freezeEffectSequenceCount = static_cast<int>(sizeof(sequence) / sizeof(sequence[0]));
    currentSequenceIndex = 0;

    ApplyEffect(currentSequenceIndex);
    timer.Reset();

    // collider
    {
        int left = static_cast<int>(position.x) - 1;
        int top = static_cast<int>(position.y) - 1;
        int right = left + GetWidth() + 2;
        int bottom = top + GetHeight() + 2;

        bodyCollider = new BoxCollider(left, top, right, bottom, -1, -1);
        CollisionSystem::Get().Register(bodyCollider);
        AddNewComponent(bodyCollider);
    }
}

void Snow::ApplyEffect(int index)
{
    if (index < 0) 
        index = 0;

    if (index >= freezeEffectSequenceCount) 
        index = freezeEffectSequenceCount - 1;

    timer.SetTargetTime(sequence[index].meltTime);
    ChangeImage(sequence[index].frame);
    hp = sequence[index].hp;
    color = sequence[index].color;
}

void Snow::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    if (isSnowballReleased)
        return;

    timer.Tick(deltaTime);
    if (!timer.IsTimeOut())
        return;

    timer.Reset();
    MeltOneStep();
}

void Snow::MeltOneStep()
{
    // 0 단계에서 더 녹으면 release
    if (currentSequenceIndex <= 0)
    {
        ReleaseSnowball();
        return;
    }

    --currentSequenceIndex;
    ApplyEffect(currentSequenceIndex);
}

void Snow::GrowOneStep()
{
    const int last = freezeEffectSequenceCount - 1;
    if (currentSequenceIndex >= last)
    {
        currentSequenceIndex = last;
        return;
    }

    ++currentSequenceIndex;
    ApplyEffect(currentSequenceIndex);
}

void Snow::ReleaseSnowball()
{
    isSnowballReleased = true;

    if (bodyCollider)
        bodyCollider->SetIsActive(false);

    if (changedEnemy)
        changedEnemy->OnSnowballReleased(position);

    Destroy();
}

void Snow::Draw()
{
    if (!isSnowballReleased)
        Actor::Draw();
}

void Snow::OnDamaged(int damage)
{
    if (isSnowballReleased)
        return;

    timer.Reset();

    hp -= damage;
    if (hp > 0)
        return;

    GrowOneStep();
}
