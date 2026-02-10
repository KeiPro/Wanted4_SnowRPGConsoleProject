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
		virtual ~MoveComponent();

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

		void OnFootEnter(BoxCollider* ground, int floorY);
		void OnFootExit(BoxCollider* ground);
		bool IsOnGrounded() const { return onGrounded; }
		virtual void Jump();
		void AddMoveSpeed(float value) 
		{ 
			if (moveSpeed >= 30.0f)
				return;

			moveSpeed += value; 
			if (moveSpeed >= 30.0f)
				moveSpeed = 30.0f;
		}

	protected:

		float moveSpeed = 15.0f;
		float jumpPower = 30.0f;
		Vector2 velocity = { 0, 0 };

		float physY = 0.0f;

		BoxCollider* footCollider = nullptr;

		std::unordered_set<BoxCollider*> groundContacts;
		bool onGrounded = false;
	};
}
