#pragma once
#include "Actor/Actor.h"
#include "Util/ItemTypes.h"

namespace Wanted
{
	class BoxCollider;
	class Item : public Actor
	{
		RTTI_DECLARATIONS(Item, Actor)

	public:
		Item(EItemType type, float value, const Vector2& pos);
		~Item();

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

	private:

		const char* GetGlyph(EItemType t) const
		{
			switch (t)
			{
				case EItemType::SpeedUp: return "S";
				case EItemType::PowerUp: return "P";
				case EItemType::RangeUp: return "R";
				default: return "?";
			}
		}

		Color GetColor(EItemType t) const
		{
			switch (t)
			{
				case EItemType::SpeedUp: return Color::BrightRed;
				case EItemType::PowerUp: return Color::BrightBlue;
				case EItemType::RangeUp: return Color::BrightYellow;
				default: return Color::White;
			}
		}

	public:

		BoxCollider* box = nullptr;
		EItemType type;
		float value;
	};
}

