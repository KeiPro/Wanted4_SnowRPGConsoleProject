#pragma once
#include "Actor/Actor.h"

namespace Wanted
{
	class AttackComponent;
	class BoxCollider;
	class Player : public Actor
	{
		RTTI_DECLARATIONS(Player, Actor)

		enum class EDir
		{
			Left,
			Right
		};

	public:
		Player(const Vector2 postiion);

		inline EDir GetDir() const {return dir;}
		inline Vector2 GetFirePos() const { return firePos; }

		void SetDir(EDir dir);
		inline void SetFirePos(Vector2 newPos) { firePos = newPos; }

		inline BoxCollider* GetFootCollider() { return footCollider; }
		inline BoxCollider* GetBodyCollider() { return bodyCollider; }

	protected:
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
		virtual void Draw() override;

	private:

		BoxCollider* footCollider = nullptr;
		BoxCollider* bodyCollider = nullptr;
		AttackComponent* attackComponent = nullptr;

		EDir dir = EDir::Right;
		Vector2 firePos = {};
	};
}
