#pragma once

#include "Component/Component.h"
#include "Common/RTTI.h"

namespace Wanted
{
	class EnemyAI : public Component
	{

		RTTI_DECLARATIONS(EnemyAI, Component)

	public:
		EnemyAI();
		~EnemyAI();

	private:
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
	};
}


