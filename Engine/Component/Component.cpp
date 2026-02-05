#include "Component.h"

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
	}

	void Component::Tick(float deltaTime)
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