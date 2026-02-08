#pragma once

#include "Component/Component.h"
#include "Common/RTTI.h"
#include "Util/Timer.h"

namespace Wanted
{
	class Player;
	class Level;
	class AttackComponent : public Component
	{
		RTTI_DECLARATIONS(AttackComponent, Component)

	public:

		AttackComponent();
		~AttackComponent();

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

		void SetSpawner(Level* l) { level = l; }

		void Fire();

	private:
		float fireInterval = 0.2f;
		Player* player = nullptr;
		Level* level = nullptr;
	};
}