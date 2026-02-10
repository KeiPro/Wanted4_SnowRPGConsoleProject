#include <iostream>
#include "AttackComponent.h"
#include "Core/Input.h"
#include "Actor/Player.h"
#include "Math/Vector2.h"
#include "Actor/PlayerBullet.h"
#include "Level/Level.h"

using namespace Wanted;

AttackComponent::AttackComponent()
{
	
}

AttackComponent::~AttackComponent()
{

}

void AttackComponent::BeginPlay()
{
	
}

void AttackComponent::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	if (Input::Get().GetKeyDown('A'))
	{
		Fire();
	}
}

void AttackComponent::Fire()
{
	if (!level)
	{
		std::cerr << "AttackComponent::Fire() / Level is null.\n";
		__debugbreak();
	}

	if (player == nullptr)
		player = GetOwner()->As<Player>();

	level->AddNewActor(new PlayerBullet(power, range, player->GetFirePos(), player->GetDir()));
}