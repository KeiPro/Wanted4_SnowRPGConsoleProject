#pragma once
#include "MoveComponent.h"
#include "Common/RTTI.h"

namespace Wanted
{
	class ThiefMoveComponent : public MoveComponent
	{
		RTTI_DECLARATIONS(ThiefMoveComponent, MoveComponent)

	public:

		ThiefMoveComponent();
		~ThiefMoveComponent();

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

		virtual void Jump() override;
	};
}

