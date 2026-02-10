#pragma once

#include "Actor/Player.h"

namespace Wanted
{
	class GameManager
	{
	public:
		GameManager();
		~GameManager();

		inline void GameOver() { isGameOver = true; }

		void SetPlayer(Player* newPlayer) { player = newPlayer; }
		inline void AddScore(int add) { this->score += add; }

		inline Player* GetPlayer() const { return player; }
		inline int GetScore() const { return score; }

		static GameManager& Get();

	public:

		Player* player = nullptr;
		int score = 0;

		bool isGameOver = false;
	};
}
