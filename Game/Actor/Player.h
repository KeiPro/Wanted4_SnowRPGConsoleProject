#pragma once
#include "Actor/Actor.h"
#include "Item.h"
#include "Util/ItemTypes.h"

namespace Wanted
{
	class MoveComponent;
	class AttackComponent;
	class BoxCollider;
	class Player : public Actor, public IItemReceiver
	{
		RTTI_DECLARATIONS(Player, Actor)

		enum class EDir
		{
			Left = -1,
			Right = 1
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
		MoveComponent* moveComponent = nullptr;

		EDir dir = EDir::Right;
		Vector2 firePos = {};

		bool isDead = false;

		void ApplyItem(EItemType type, float value) override;
	};
}
