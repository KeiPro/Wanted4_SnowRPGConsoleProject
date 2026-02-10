#pragma once
#include <vector>

//#include "Actor/Player.h"
#include "Actor/Enemy/EnemySpawner.h"
#include "Actor/ItemSpawner.h"

namespace Wanted
{
	class Spawner;
	class Player;
	class GameManager
	{
	public:
		GameManager();
		~GameManager();

		inline void GameOver() { isGameOver = true; }

		void SetPlayer(Player* newPlayer) { player = newPlayer; }
		inline void AddScore(int add) { this->score += add; }
		void AddSpawner(Spawner* spawner);
		void AddItemSpawner(Spawner* spawner);

		inline Player* GetPlayer() const { return player; }
		inline int GetScore() const { return score; }

		static GameManager& Get();

	public:

		Player* player = nullptr;
		int score = 0;

		bool isGameOver = false;

	private:

		//std::vector<Spawner*> spawners;
		EnemySpawner* enemySpawner = nullptr;
		ItemSpawner* itemSpawner = nullptr;
	};
}
