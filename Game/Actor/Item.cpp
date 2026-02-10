#include "Item.h"
#include "Component/Collider/BoxCollider.h"
#include "Util/ItemTypes.h"
#include "Physics/CollisionSystem.h"

using namespace Wanted;

Item::Item(EItemType type, float value, const Vector2& pos)
	: super(GetGlyph(type), pos, GetColor(type))
	, type(type), value(value)
{

    sortingOrder = 2;
    int left = static_cast<int>(position.x) - 1;
    int top = static_cast<int>(position.y) - 1;
    int right = left + 2;
    int bottom = top + 2;

    box = new BoxCollider(left, top, right, bottom, 0, 1);

    box->SetOnEnter([](BoxCollider* self, BoxCollider* other)
        {
            Actor* owner = self->GetOwner();
            Item* item = owner->As<Item>();
            if (!item) return;

            Actor* otherOwner = other->GetOwner();

            IItemReceiver* receiver = dynamic_cast<IItemReceiver*>(otherOwner);
            if (receiver)
            {
                receiver->ApplyItem(item->type, item->value);
                owner->Destroy();
                self->SetIsActive(false);
            }
        });

    box->SetOnStay([](BoxCollider* self, BoxCollider* other)
        {
            Actor* owner = self->GetOwner();
            Item* item = owner->As<Item>();
            if (!item) return;

            Actor* otherOwner = other->GetOwner();

            IItemReceiver* receiver = dynamic_cast<IItemReceiver*>(otherOwner);
            if (receiver)
            {
                receiver->ApplyItem(item->type, item->value);
                owner->Destroy();
                self->SetIsActive(false);
            }
        });

    AddNewComponent(box);
    CollisionSystem::Get().Register(box);
}

Item::~Item()
{
}

void Item::BeginPlay()
{
    Actor::BeginPlay();
}

void Item::Tick(float dt)
{
    super::Tick(dt);
}