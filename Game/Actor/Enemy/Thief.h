#pragma once
#include "Enemy.h"
#include "Common/RTTI.h"

#include <vector>

namespace Wanted
{
	class BoxCollider;
	class ThiefMoveComponent;
	class Thief : public Enemy
	{
		RTTI_DECLARATIONS(Thief, Enemy)

	public:
		Thief(const Vector2 position);
		~Thief();

		inline BoxCollider* GetFootCollider() { return footCollider; }
		inline BoxCollider* GetBodyCollider() { return bodyCollider; }

	private:
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
		virtual void Draw() override;

		virtual void UpdateIdle(float deltaTime) override;
		virtual void UpdateChase(float deltaTime) override;
		virtual void UpdateAttack(float deltaTime) override;
		virtual void Dead() override;

		bool CheckPlayerXRange(float myPosX, float playerPosX);

	private:

		Vector2 initialPosition = {};
		int chaseCount = 0;
		int chaseRange = 0;
		int moveDir = 1;

		float elapsedTime = 0.0f;
		float changeDirInterval = 1.5f;
		bool needChangeDir = false;

		float jumpElapsedTime = 0.0f;
		float jumpInterval = 2.0f;

		BoxCollider* footCollider = nullptr;
		BoxCollider* bodyCollider = nullptr;
		ThiefMoveComponent* thiefMoveComp = nullptr;
	};
}

