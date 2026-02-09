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

		virtual void Draw() override;

	private:
		void LoadMap(const char* filename);
		
		bool CheckGameClear();

	private:
		int targetScore = 0;
		bool isGameClear = false;
	};
}
