#pragma once
#include "Actor/Actor.h"
#include "Util/Timer.h"
#include "Interface/IDamageable.h"

namespace Wanted
{
	class Enemy;
	class Snow : public Actor, public IDamageable
	{
		RTTI_DECLARATIONS(Snow, Actor)

		struct FreezeEffect
		{
			FreezeEffect(
				const char* frame,
				float meltTime = 0.05f,
				int hp = 2,
				Color color = Color::Red)
				: meltTime(meltTime), hp(hp), color(color)
			{
				size_t length = strlen(frame) + 1;
				this->frame = new char[length];
				strcpy_s(this->frame, length, frame);
			}

			~FreezeEffect()
			{
				delete[] frame;
				frame = nullptr;
			}

			char* frame = nullptr;
			float meltTime = 0.0f;
			int hp = 2;
			Color color = Color::Blue;
		};

	public:
		Snow(const Vector2& position, Enemy* changedEnemy);
		~Snow();

		virtual void Tick(float deltaTime) override;

		void OnDamaged(int damage) override;

	public:
		int freezeEffectSequenceCount = 0;
		int currentSequenceIndex = 0;
		Timer timer;
		int hp = 1;

	private:
		Enemy* changedEnemy = nullptr;
	};
}


