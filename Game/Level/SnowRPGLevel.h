#pragma once
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class SnowRPGLevel : public Wanted::Level
{
	RTTI_DECLARATIONS(SnowRPGLevel, Level)

public:
	SnowRPGLevel();

	virtual void Draw() override;

private:
	void LoadMap(const char* filename);

	bool CheckGameClear();

private:
	int targetScore = 0;

	bool isGameClear = false;
};