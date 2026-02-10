#pragma once
#include "MoveComponent.h"

#include "Common/RTTI.h"

namespace Wanted
{
	class PlayerMoveComponent : public MoveComponent
	{
		RTTI_DECLARATIONS(PlayerMoveComponent, MoveComponent)

	public:

		PlayerMoveComponent();
		~PlayerMoveComponent();

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

		bool isDroppingDown = false;
		float dropDisableTimer = 0.0f;
		float dropDisableDuration = 0.15f;
	};
}
