#pragma once

#include "Common/Common.h"

namespace Wanted
{
	class Input;
	class Renderer;
	class CollisionSystem;

	// Main game engine class.
	class WANTED_API Engine
	{
		struct EngineSetting
		{
			float frameRate = 0.0f;
			int width = 0;
			int height = 0;
		};

	public:
		Engine();
		virtual ~Engine();

		void Run();

		void QuitEngine();

		int GetWidth()  const { return setting.width; }

		int GetHeight() const { return setting.height; }

		void SetNewLevel(class Level* newLevel);
		Level* GetLevel() { return mainLevel; }

		static Engine& Get();

	protected:

		void Shutdown();

		void LoadSetting();

		void BeginPlay();

		void Tick(float deltaTime);

		void Draw();


	protected:
		bool isQuit = false;

		EngineSetting setting;

		Input* input = nullptr;
		
		Renderer* renderer = nullptr;

		CollisionSystem* collisionSystem = nullptr;

		class Level* mainLevel = nullptr;

		static Engine* instance;
	};
}

