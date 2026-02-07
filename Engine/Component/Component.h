#pragma once

#include "Common/RTTI.h"

namespace Wanted
{
	class Actor;
	class WANTED_API Component : public RTTI
	{
		RTTI_DECLARATIONS(Component, RTTI)

	public:

		Component();
		virtual ~Component();

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		void Destory();
		virtual void OnDestroy();

		void SetOwner(Actor* newOwner) { owner = newOwner; }
		inline Actor* GetOwner() const { return owner; }

		inline bool DestroyRequested() const { return destroyRequested; }
		inline bool HasBeganPlay() const { return hasBeganPlay; }

		inline bool GetIsActive() const { return isActive; }
		inline void SetIsActive(bool newIsActive) { isActive = newIsActive; }

	private:

		bool hasBeganPlay = false;
		bool isActive = false;
		bool destroyRequested = false;

		Actor* owner = nullptr;
	};
}



