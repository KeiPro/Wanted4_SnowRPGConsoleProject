#pragma once
#include "Enemy.h"
#include "Common/RTTI.h"

#include <vector>

namespace Wanted
{
	class BoxCollider;
	class Thief : public Enemy
	{
		RTTI_DECLARATIONS(Thief, Enemy)

	public:
		Thief(const Vector2 position);
		~Thief();

	private:
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
		virtual void Draw() override;

		virtual void UpdateIdle(float deltaTime) override;
		virtual void UpdateChase(float deltaTime) override;
		virtual void UpdateAttack(float deltaTime) override;
		virtual void Dead() override;

	private:

		Vector2 initialPosition = {};
		int chaseCount = 0;
		int chaseRange = 0;
		int moveDir = 1;

		BoxCollider* bodyCollider = nullptr;
		float elapsedTime = 0.0f;
		float changeDirInterval = 1.5f;
		bool needChangeDir = false;
	};
}

