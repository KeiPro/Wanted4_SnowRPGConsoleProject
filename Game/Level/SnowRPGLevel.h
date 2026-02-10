#pragma once
#include "Level/Level.h"
#include "Interface/ISpawner.h"

namespace Wanted
{
	class SnowRPGLevel : public Level
	{
		RTTI_DECLARATIONS(SnowRPGLevel, Level)

	public:
		SnowRPGLevel();
		~SnowRPGLevel();

		void DrawGameClear();
		void DrawGameOver();

		virtual void Draw() override;
		
		void DrawScore();

	private:
		void LoadMap(const char* filename);
		
	private:
		int targetScore = 0;

		Vector2 screenSize = {};
	};
}
