#pragma once
#include "Actor/Actor.h"

//using namespace Wanted;
namespace Wanted
{
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

		inline EDir GetDir() const { return dir; }

		void SetDir(EDir dir);
		void OnChangedDir(EDir oldDir, EDir newDir);
		void UpdateSideColliderOffset();

		inline BoxCollider* GetFootCollider() { return footCollider; }
		inline BoxCollider* GetSideCollider() { return sideCollider; }
		inline BoxCollider* GetBodyCollider() { return bodyCollider; }

	protected:
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
		virtual void Draw() override;

	private:

		BoxCollider* footCollider = nullptr;
		BoxCollider* sideCollider = nullptr;
		BoxCollider* bodyCollider = nullptr;

		EDir dir = EDir::Right;
	};
}
