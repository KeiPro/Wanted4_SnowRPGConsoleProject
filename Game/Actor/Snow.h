#pragma once
#include "Actor/Actor.h"
#include "Util/Timer.h"
#include "Interface/IDamageable.h"

namespace Wanted
{
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
				// 문자열 설정.
				size_t length = strlen(frame) + 1;
				this->frame = new char[length];
				strcpy_s(this->frame, length, frame);
			}

			~FreezeEffect()
			{
				delete[] frame;
				frame = nullptr;
			}

			// 문자열 변수 (화면에 보여줄 문자열).
			char* frame = nullptr;
			float meltTime = 0.0f;
			int hp = 2;
			Color color = Color::Blue;
		};

	public:
		Snow(const Vector2& position);
		~Snow();

		virtual void Tick(float deltaTime) override;

		void OnDamaged(int damage) override;

	public:
		int freezeEffectSequenceCount = 0;
		int currentSequenceIndex = 0;
		Timer timer;
		int hp = 1;

		
	};
}


