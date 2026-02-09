#include "Engine.h"
#include "Level/Level.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Render/Renderer.h"

#include <iostream>
#include <Windows.h>

namespace Wanted
{
	Engine* Engine::instance = nullptr;

	Engine::Engine()
	{
		instance = this;

		input = new Input();

		LoadSetting();

		renderer = new Renderer(Vector2(setting.width, setting.height));

		Util::TurnOffCursor();

		Util::SetRandomSeed();
	}

	Engine::~Engine()
	{
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}

		if (input)
		{
			delete input;
			input = nullptr;
		}

		SafeDelete(renderer);
	}

	void Engine::Run()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		int64_t currentTime = 0;
		int64_t previousTime = 0;

		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);

		currentTime = time.QuadPart;
		previousTime = currentTime;

		//float targetFrameRate = 120;
		setting.frameRate = setting.frameRate == 0.0f ? 60.0f : setting.frameRate;
		float oneFrameTime = 1.0f / setting.frameRate;

		while (!isQuit)
		{
			QueryPerformanceCounter(&time);
			currentTime = time.QuadPart;

			float deltaTime = static_cast<float>(currentTime - previousTime);

			deltaTime = deltaTime / static_cast<float>(frequency.QuadPart);

			if (deltaTime >= oneFrameTime)
			{
				input->ProcessInput();

				BeginPlay();
				Tick(deltaTime);
				Draw();

				previousTime = currentTime;

				input->SavePreviousInputStates();

				if (mainLevel)
				{
					mainLevel->ProcessAddAndDestroyActors();
				}
			}
		}

		Shutdown();
	}

	void Engine::QuitEngine()
	{
		isQuit = true;
	}

	void Engine::SetNewLevel(Level* newLevel)
	{
		if (mainLevel)
		{
			delete mainLevel;
			mainLevel = nullptr;
		}

		mainLevel = newLevel;
	}

	Engine& Engine::Get()
	{
		if (!instance)
		{
			std::cout << "Error : Engine::Get(). instance is null\n";
			__debugbreak();
		}

		return *instance;
	}

	void Engine::Shutdown()
	{
		std::cout << "Engine has been shutdown...\n";

		Util::TurnOnCursor();
	}

	void Engine::LoadSetting()
	{
		FILE* file = nullptr;
		fopen_s(&file, "../Config/Setting.txt", "rt"); // read text
		if (file == nullptr)
		{
			std::cout << "Failed to open engine setting file.\n";
			__debugbreak();
			return;
		}

		char buffer[2048] = {};

		size_t readSize = fread(buffer, sizeof(char), 2048, file);

		char* context = nullptr;
		char* token = nullptr;
		token = strtok_s(buffer, "\n", &context);

		while (token)
		{
			char header[10] = {};
			sscanf_s(token, "%s", header, 10);

			if (strcmp(header, "framerate") == 0)
			{
				sscanf_s(token, "framerate = %f", &setting.frameRate);
			}
			else if (strcmp(header, "width") == 0)
			{
				sscanf_s(token, "width = %d", &setting.width);
			}
			else if (strcmp(header, "height") == 0)
			{
				sscanf_s(token, "height = %d", &setting.height);
			}

			token = strtok_s(nullptr, "\n", &context);
		}

		fclose(file);
	}

	void Engine::BeginPlay()
	{
		if (mainLevel == nullptr)
		{
			std::cout << "mainLevel is empty.\n";
			return;
		}

		mainLevel->BeginPlay();
	}

	void Engine::Tick(float deltaTime)
	{
		if (!mainLevel)
		{
			std::cout << "Error: Engine::Tick(). mainLevel is empty. \n";
			return;
		}

		mainLevel->Tick(deltaTime);
	}

	void Engine::Draw()
	{
		if (!mainLevel)
		{
			std::cout << "Error: Engine::Draw(). mainLevel is empty. \n";
			return;
		}
		
		mainLevel->Draw();

		renderer->Draw();
	}

}
