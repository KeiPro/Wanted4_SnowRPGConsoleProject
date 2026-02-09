#pragma once

#include "Actor/Player.h"

namespace Wanted
{
	class GameManager
	{
	public:
		GameManager();
		~GameManager();

		void SetPlayer(Player* newPlayer) { player = newPlayer; }

		Player* GetPlayer() { return player; }

		static GameManager& Get();

	public:

		Player* player = nullptr;
	};
}
