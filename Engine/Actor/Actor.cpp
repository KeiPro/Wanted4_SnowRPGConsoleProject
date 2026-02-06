#include "Actor.h"
#include "Render/Renderer.h"
#include "Util/Util.h"
#include "Engine/Engine.h"
#include "Component/Component.h"
#include "Math/Vector2.h"

#include <iostream>
#include <Windows.h>

namespace Wanted
{
	Actor::Actor(const char* image, const Vector2& position, Color color)
		: position(position), color(color)
	{
		size_t length = strlen(image) + 1;
		this->image = new char[length];
		strcpy_s(this->image, length, image);

		width = length - 1;
		height = 1;
	}

	Actor::~Actor()
	{
		SafeDeleteArray(this->image);

		for (Component* component : components)
		{
			delete component;
			component = nullptr;
		}
	}

	void Actor::BeginPlay()
	{
		hasBeganPlay = true;

		for (Component* component : components)
		{
			if (component->HasBeganPlay())
				continue;

			component->BeginPlay();
		}
	}

	void Actor::Tick(float deltaTime)
	{
		for (Component* component : components)
		{
			component->Tick(deltaTime);
		}
	}

	void Actor::Draw()
	{
		Renderer::Get().Submit(image, position, color, sortingOrder);

		for (Component* component : components)
		{
			if (component->GetIsActive() == false)
				continue;

			component->Draw();
		}
	}

	void Actor::Destroy()
	{
		destroyRequested = true;

		OnDestroy();
	}

	void Actor::OnDestroy()
	{

	}

	void Actor::QuitGame()
	{
		Engine::Get().QuitEngine();
	}

	bool Actor::TestIntersect(const Actor* const other)
	{
		// AABB(Axis Aligned Bounding Box).
		int xMin = position.x;
		int xMax = position.x + width - 1;

		int otherXMin = other->GetPosition().x;
		int otherXMax = other->GetPosition().x + other->GetWidth() - 1;

		if (otherXMin > xMax)
			return false;

		if (otherXMax < xMin)
			return false;

		return position.y == other->position.y;
	}

	void Actor::SetPosition(const Vector2& newPosition)
	{
		if (position == newPosition)
			return;

		position = newPosition;
	}

	void Actor::AddNewComponent(Component* newComponent)
	{
		components.emplace_back(newComponent);

		newComponent->SetOwner(this);
	}

	void Actor::ProcessAddAndDestroyComponent()
	{
		for (int i = 0; i < static_cast<int>(components.size()); )
		{
			if (components[i]->DestroyRequested())
			{
				delete components[i];
				components.erase(components.begin() + i);
				continue;
			}

			++i;
		}

		if (addRequestedComponents.size() == 0)
			return;

		for (Component* const component : addRequestedComponents)
		{
			components.emplace_back(component);
		}

		addRequestedComponents.clear();
	}
}