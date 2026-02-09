#pragma once
#include "Actor/Actor.h"
#include "Common/RTTI.h"

namespace Wanted
{
	class Enemy : public Actor
	{
		RTTI_DECLARATIONS(Enemy, Actor)

			enum class EnemyState
		{
			Idle,
			Chase,
			Attack,
			Dead,
		};

	public:

		Enemy(const char* image, const Vector2& position, Color color);
		~Enemy();

	protected:

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
		virtual void Draw() override;

		virtual void UpdateIdle(float deltaTime);
		virtual void UpdateChase(float deltaTime);
		virtual void UpdateAttack(float deltaTime);
		virtual void Dead();

	protected:

		EnemyState state = EnemyState::Idle;;
		bool isDead = false;
		int moveSpeed = 10;
	};
}
