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
		void AddPowerUp(float value)
		{
			power += value;
			if (power > 5)
				power = 5;
		}
		
		void AddRangeUp(float value)
		{
			range += value;
			if (range >= 100.0f)
				range = 100.0f;
		}

		void Fire();

	public:
		int power = 1;
		float range = 50.0f;

	private:
		float fireInterval = 0.2f;
		Player* player = nullptr;
		Level* level = nullptr;
		
	};
}