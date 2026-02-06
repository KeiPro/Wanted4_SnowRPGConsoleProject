#pragma once

#include "Common/RTTI.h"

#include "Component/Component.h"
#include "Math/Vector2.h"

namespace Wanted
{
	class WANTED_API BoxCollider : public Component
	{
		RTTI_DECLARATIONS(BoxCollider, Component)

	public:

		using CollisionCallback = void(*)(BoxCollider* self, BoxCollider* const other);
		using OnCollisionExit = void(*)(BoxCollider* self);

		BoxCollider(int left, int top, int right, int bottom, int offsetX = 0, int offsetY = 0);
		~BoxCollider();
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
		virtual void Draw() override;

		bool AABBCollision(const BoxCollider* const other);
		void SetPosition(int left, int top);
		void NotifyCollision(BoxCollider* const other);
		
		inline void SetCollisionCallback(CollisionCallback callback) { onCollision = callback; }

	public:

		bool debugMode = false;

	private:

		int left, top, right, bottom;
		int offsetX = 0, offsetY = 0;
		Vector2 size = {};

		CollisionCallback onCollision = nullptr;
		OnCollisionExit onCollisionExit = nullptr;
	};
}

