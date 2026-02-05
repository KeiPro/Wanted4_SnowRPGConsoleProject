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

		BoxCollider(int left, int top, int right, int bottom);
		~BoxCollider();

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

		bool AABBCollision(const BoxCollider* const other);
		void SetPosition(int left, int top);

	private:

		int left, top, right, bottom;
		Vector2 size = {};
	};
}

