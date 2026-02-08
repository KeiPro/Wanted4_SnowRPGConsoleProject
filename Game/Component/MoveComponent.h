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

		inline bool IsOnGrounded() const { return onGrounded; }
		void RequestOnGrounded(int floorY);
		void TryMoveX(Vector2& pos, float dx);

		void OnFootEnter(BoxCollider* ground);
		void OnFootExit(BoxCollider* ground);

	private:

		float moveSpeed = 30.0f;
		float jumpPower = 30.0f;
		Vector2 velocity = { 0, 0 };

		float physY = 0.0f;

		BoxCollider* footCollider = nullptr;

		std::unordered_set<BoxCollider*> groundContacts;
		bool onGrounded = false;
	};
}
