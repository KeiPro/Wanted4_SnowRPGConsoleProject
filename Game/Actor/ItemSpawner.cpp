#include "ItemSpawner.h"
#include "Item.h"
#include "Util/Util.h"
#include "Level/Level.h"
#include "Render/Renderer.h"
#include "Util/ItemTypes.h"

using namespace Wanted;

ItemSpawner::ItemSpawner()
{
	timer.SetTargetTime(baseSpawnTime);
}

ItemSpawner::~ItemSpawner()
{
	
}

void ItemSpawner::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if (isSelected == false)
	{
		if (spawners.size() == 0)
			return;

		isSelected = true;
		int spawnIndex = Util::Random(0, spawners.size() - 1);
		spawnPos = spawners[spawnIndex]->GetPosition();
		return;
	}

	timer.Tick(deltaTime);
	if (!timer.IsTimeOut())
		return;

	timer.Reset();
	SpawnItem(deltaTime);
	isSelected = false;
}

void ItemSpawner::SpawnItem(float deltaTime)
{
    EItemType type = static_cast<EItemType>(Util::Random(0, 2));

    float value = 0.f;

    switch (type)
    {
    case EItemType::SpeedUp:
        value = 3.0f;
        break;

    case EItemType::PowerUp:
        value = 1.0f;
        break;

    case EItemType::RangeUp:
        value = 5.0f;
        break;
    }

    GetOwner()->AddNewActor(new Item(type, value, spawnPos));
}