#include "Snow.h"
#include "Actor/Enemy/Enemy.h"
#include "Component/Collider/BoxCollider.h"
#include "Physics/CollisionSystem.h"
#include "Util/GameConstants.h"
#include "Actor/Envrionments/En_Wall.h"
#include "Engine/Engine.h"
#include "Manager/GameManager.h"
#include "Player.h"

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

    {
        int left = static_cast<int>(position.x);
        int top = static_cast<int>(position.y) + 1;
        int right = left + 1;
        int bottom = top + 1;

        footCollider = new BoxCollider(left, top, right, bottom, 0, 1);

        footCollider->SetOnEnter([](BoxCollider* self, BoxCollider* other)
        {
            if (!other || !other->GetOwner() || !other->GetOwner()->IsTypeOf<En_Wall>())
                return;

            Snow* snow = self->GetOwner()->As<Snow>();
            snow->OnFootEnter(other, other->GetOwner()->GetPosition().y - 1);
        });

        footCollider->SetOnExit([](BoxCollider* self, BoxCollider* other)
        {
            if (!other || !other->GetOwner() || !other->GetOwner()->IsTypeOf<En_Wall>())
                return;

            Snow* snow = self->GetOwner()->As<Snow>();
            snow->OnFootExit(other);
        });

        CollisionSystem::Get().Register(footCollider);
        AddNewComponent(footCollider);
    }

    // Body Collider
    {
        int left = static_cast<int>(position.x) - 1;
        int top = static_cast<int>(position.y) - 1;
        int right = left + GetWidth() + 2;
        int bottom = top + GetHeight() + 2;

        bodyCollider = new BoxCollider(left, top, right, bottom, -1, -1);
        CollisionSystem::Get().Register(bodyCollider);
        AddNewComponent(bodyCollider);
    }

    if (bodyCollider)
        bodyCollider->SetIsActive(true);

    if (footCollider)
        footCollider->SetIsActive(true);
}

void Snow::OnFootEnter(BoxCollider* ground, int floorY)
{
    groundContacts.insert(ground);
    onGround = true;
    physY = floorY;
    velocity.y = 0.f;
}

void Snow::OnFootExit(BoxCollider* ground)
{
    groundContacts.erase(ground);
    onGround = !groundContacts.empty();
}

void Snow::ApplyEffect(int index)
{
    if (index < 0) 
        index = 0;

    if (index >= freezeEffectSequenceCount) 
        index = freezeEffectSequenceCount - 1;

    const auto& e = sequence[index];
    timer.SetTargetTime(e.meltTime);
    ChangeImage(e.frame);
    hp = e.hp;
    color = e.color;
}

void Snow::BeginPlay()
{
    super::BeginPlay();
	physY = position.y;
}

void Snow::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    if (isSnowballReleased)
        return;

    if (mode == ESnowMode::Frozen)
        TickFrozen(deltaTime);
    else
        TickProjectile(deltaTime);
}

void Snow::TickFrozen(float dt)
{
    timer.Tick(dt);
    if (!timer.IsTimeOut())
        return;

    timer.Reset();
    MeltOneStep();
}

void Snow::TickProjectile(float dt)
{
    Vector2 pos = GetPosition();

    const int mapW = Engine::Get().GetWidth();
    const float minX = 1.0f;
    const float maxX = static_cast<float>((mapW - 1) - (GetWidth() - 1));

    float nextX = pos.x + velocity.x * dt;

    if (nextX > maxX)
    {
        float over = nextX - maxX;
        pos.x = maxX - over;
        BounceX();
    }
    else if (nextX < minX)
    {
        float over = minX - nextX;
        pos.x = minX + over;
        BounceX();
    }
    else
    {
        pos.x = nextX;
    }

    if (onGround)
    {
        if (velocity.y > 0.0f)
            velocity.y = 0.0f;
    }
    else
    {
        velocity.y += GameConst::Gravity * dt;
        physY += velocity.y * dt;
    }

    pos.y = (int)physY;
    SetPosition(pos);
}

void Snow::MeltOneStep()
{
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
        Launch((int)GameManager::Get().GetPlayer()->GetDir());
        return;
    }

    ++currentSequenceIndex;
    ApplyEffect(currentSequenceIndex);
}

void Snow::ReleaseSnowball()
{
    isSnowballReleased = true;

    // 충돌 끄기
    if (bodyCollider) 
        bodyCollider->SetIsActive(false);

    if (footCollider)
        footCollider->SetIsActive(false);

    // Enemy 복구
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

    if (mode == ESnowMode::Projectile)
        return;

    timer.Reset();

    hp -= damage;
    if (hp > 0)
        return;

    GrowOneStep();
}

void Snow::Launch(int dirX)
{
    if (isSnowballReleased)
        return;

    if (mode == ESnowMode::Projectile)
        return;

    mode = ESnowMode::Projectile;

    timer.Reset();

    const int sign = (dirX >= 0) ? 1 : -1;
    velocity.x = launchSpeedX * static_cast<float>(sign);
    velocity.y = 0.0f;

    remainingBounces = 3;
    onGround = false;
}

void Snow::BounceX()
{
    if (mode != ESnowMode::Projectile)
        return;

    velocity.x *= -1.0f;

    --remainingBounces;
    if (remainingBounces <= 0)
        KillProjectile();
}

void Snow::KillProjectile()
{
    isSnowballReleased = true;

    if (bodyCollider) 
        bodyCollider->SetIsActive(false);

    if (footCollider)
        footCollider->SetIsActive(false);

    Destroy();
}
