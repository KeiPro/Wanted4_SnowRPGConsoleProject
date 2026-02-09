#pragma once
#include "Enemy.h"

#include "Common/RTTI.h"

namespace Wanted
{
	class Fly : public Enemy
	{
		RTTI_DECLARATIONS(Fly, Enemy)

	public:
		Fly(const Vector2 position);
		~Fly();

	private:
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

	};
}
