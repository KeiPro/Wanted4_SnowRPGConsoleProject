#include "Component.h"
#include <iostream>

namespace Wanted
{
	Component::Component()
	{
	}

	Component::~Component()
	{
	}

	void Component::BeginPlay()
	{
		hasBeganPlay = true;
		isActive = true;
	}

	void Component::Tick(float deltaTime)
	{

	}

	void Component::Draw()
	{

	}

	void Component::Destory()
	{
		destroyRequested = true;

		OnDestroy();
	}

	void Component::OnDestroy()
	{

	}
}