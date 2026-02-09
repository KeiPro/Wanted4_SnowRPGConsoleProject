#pragma once
#include "Component/Component.h"
#include "Math/Vector2.h"
#include "Common/RTTI.h"

#include <unordered_set>

namespace Wanted
{
	class BoxCollider;
	class MoveComponent : public Component
	{
		RTTI_DECLARATIONS(MoveComponent, Component)

	public:

		MoveComponent();
		~MoveComponent();

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

		void OnFootEnter(BoxCollider* ground, int floorY);
		void OnFootExit(BoxCollider* ground);

	protected:

		inline bool IsOnGrounded() const { return onGrounded; }
		
		void Jump();

	protected:

		float moveSpeed = 30.0f;
		float jumpPower = 30.0f;
		Vector2 velocity = { 0, 0 };

		float physY = 0.0f;

		BoxCollider* footCollider = nullptr;

		std::unordered_set<BoxCollider*> groundContacts;
		bool onGrounded = false;
	};
}
