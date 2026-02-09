#pragma once

#include "Common/RTTI.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Component/Component.h"

#include <vector>

namespace Wanted
{
	//class Component;
	class Level;
	class WANTED_API Actor : public RTTI
	{
		RTTI_DECLARATIONS(Actor, RTTI)

	public:
		Actor(const char* image = " ",
			const Vector2 & position = Vector2::Zero, 
			Color color = Color::White);

		virtual ~Actor();

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		void Destroy();

		virtual void OnDestroy();

		void QuitGame();

		bool TestIntersect(const Actor* const other);

		void SetPosition(const Vector2& newPosition);
		inline Vector2 GetPosition() const { return position; }

		void SetOwner(Level* newOwner) { owner = newOwner; }
		inline Level* GetOwner() const { return owner; }

		void AddNewComponent(Component* newComponent);
		
		template<typename T>
		T* GetComponent()
		{
			for (Component* const component : components)
			{
				if (T* casted = component->As<T>())
					return casted;
			}
			return nullptr;
		}

		template<typename T>
		const T* GetComponent() const
		{
			for (Component* const component : components)
			{
				if (const T* casted = component->As<T>())
					return casted;
			}
			return nullptr;
		}

		void ProcessAddAndDestroyComponent();

		void ChangeImage(const char* newImage);

		// Getter
		inline bool HasBeganPlay() const { return hasBeganPlay; }
		inline bool IsActive() const { return isActive && !destroyRequested; }
		inline bool DestroyRequested() const { return destroyRequested; }
		inline int GetSortingOrder() const { return sortingOrder; }
		inline int GetWidth() const { return width; }
		inline int GetHeight() const { return height; }

	public:
		char* image = nullptr;

		int width = 0;
		int height = 0;

	protected:
		bool hasBeganPlay = false;

		bool isActive = true;

		bool destroyRequested = false;



		Color color = Color::White;

		Level* owner = nullptr;

		int sortingOrder = 0;

		Vector2 position;

		std::vector<Component*> components;
		std::vector<Component*> addRequestedComponents;
	};
}

