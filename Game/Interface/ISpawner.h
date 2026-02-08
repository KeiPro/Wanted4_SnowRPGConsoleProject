#pragma once
#include "Actor/Actor.h"

struct ISpawner {
	virtual void Spawn(Wanted::Actor* actor) = 0;
	virtual ~ISpawner() = default;
};