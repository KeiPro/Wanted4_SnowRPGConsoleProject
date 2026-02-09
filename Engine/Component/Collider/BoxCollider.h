#pragma once

#include "Common/RTTI.h"

#include "Component/Component.h"
#include "Math/Vector2.h"
#include "Math/Color.h"

namespace Wanted
{
	class WANTED_API BoxCollider : public Component
	{
		RTTI_DECLARATIONS(BoxCollider, Component)

	public:
		
		using CollisionCallback = void(*)(BoxCollider* self, BoxCollider* const other);

		BoxCollider(int left, int top, int right, int bottom, int offsetX = 0, int offsetY = 0);
		~BoxCollider();
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
		virtual void Draw() override;
		virtual void OnDestroy() override;

		bool AABBCollision(const BoxCollider* const other);
		
		void SyncToOwner();
		void SetOffset(int offsetX, int offsetY);

		void SetOnEnter(CollisionCallback cb) { onEnter = cb; }
		void SetOnStay(CollisionCallback cb) { onStay = cb; }
		void SetOnExit(CollisionCallback cb) { onExit = cb; }

		void NotifyEnter(BoxCollider* other) { if (onEnter) onEnter(this, other); }
		void NotifyStay(BoxCollider* other) { if (onStay) onStay(this, other); }
		void NotifyExit(BoxCollider* other) { if (onExit) onExit(this, other); }

	public:

		bool debugMode = false;
		Color debugColor = Color::White;

	private:

		int left, top, right, bottom;
		int offsetX = 0, offsetY = 0;
		Vector2 size = {};

		CollisionCallback onEnter = nullptr;
		CollisionCallback onStay = nullptr;
		CollisionCallback onExit = nullptr;
	};
}

